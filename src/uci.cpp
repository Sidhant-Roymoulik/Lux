#include "uci.h"

#include "bench.h"
#include "eval.h"
#include "thread.h"

using namespace chess;

int current_hash_size = DEFAULT_HASH_SIZE;
int prev_hash_size    = current_hash_size;

static constexpr float SP_LO = 0.5f;  // min = value * SP_LO
static constexpr float SP_HI = 2.0f;  // max = value * SP_HI

bool IsUci = false;

TranspositionTable* table;

static void uci_send_id() {
    printf("id name Lux %s\n", VERSION);
    printf("id author %s\n", AUTHOR);

    printf("option name Hash type spin default %d min %d max %d\n", DEFAULT_HASH_SIZE, MIN_HASH_SIZE, MAX_HASH_SIZE);
    printf("option name Threads type spin default 1 min 1 max %d\n", MAX_THREADS);

    // SPSA-tunable search parameters
    printf("option name AspWindow    type spin   default %d min %d max %d\n", SP.asp_window,
           (int)(SP.asp_window * SP_LO), (int)(SP.asp_window * SP_HI));
    printf("option name AspDivisor   type spin   default %d min %d max %d\n", SP.asp_divisor,
           (int)(SP.asp_divisor * SP_LO), (int)(SP.asp_divisor * SP_HI));
    printf("option name AspDeltaDiv  type spin   default %d min %d max %d\n", SP.asp_delta_div,
           (int)(SP.asp_delta_div * SP_LO), (int)(SP.asp_delta_div * SP_HI));
    printf("option name RfpMargin    type string default %.1f\n", SP.rfp_margin);
    printf("option name RfpDepth     type spin   default %d min %d max %d\n", SP.rfp_depth, (int)(SP.rfp_depth * SP_LO),
           (int)(SP.rfp_depth * SP_HI));
    printf("option name NmpBase      type string default %.1f\n", SP.nmp_base);
    printf("option name NmpDivisor   type string default %.1f\n", SP.nmp_divisor);
    printf("option name LmrBase      type string default %.2f\n", SP.lmr_base);
    printf("option name LmrDivisor   type string default %.2f\n", SP.lmr_divisor);
    printf("option name LmrMoveMin   type spin   default %d min %d max %d\n", SP.lmr_move_min,
           (int)(SP.lmr_move_min * SP_LO), (int)(SP.lmr_move_min * SP_HI));
    printf("option name HistPrune    type spin   default %d min %d max %d\n", SP.hist_prune,
           (int)(SP.hist_prune * SP_LO), (int)(SP.hist_prune * SP_HI));
    printf("option name HistBonusMul type string default %.2f\n", SP.hist_bonus_mul);

    std::cout << "uciok" << std::endl;
}

static void handle_go(std::istringstream& is, SearchThread& st, ThreadHandler& thread_handler) {
    std::string token;
    is >> std::skipws >> token;

    st.tm.reset();
    st.time_set  = false;
    st.nodes_set = false;

    int depth     = -1;
    int64_t nodes = -1;

    while (token != "none") {
        if (token == "infinite") {
            depth = -1;
            break;
        }

        if (token == "movestogo") {
            is >> std::skipws >> token;
            st.tm.movestogo = stoi(token);
        } else if (token == "depth") {
            is >> std::skipws >> token;
            depth = std::stoi(token);
        } else if (token == "wtime") {
            is >> std::skipws >> token;
            st.tm.wtime = std::stod(token);
        } else if (token == "btime") {
            is >> std::skipws >> token;
            st.tm.btime = std::stod(token);
        } else if (token == "winc") {
            is >> std::skipws >> token;
            st.tm.winc = std::stod(token);
        } else if (token == "binc") {
            is >> std::skipws >> token;
            st.tm.binc = std::stod(token);
        } else if (token == "movetime") {
            is >> std::skipws >> token;
            st.tm.movetime = std::stod(token);
        } else if (token == "nodes") {
            is >> std::skipws >> token;
            nodes = stoi(token);
        }

        if (!(is >> std::skipws >> token)) break;
    }

    if (nodes != -1) {
        st.node_limit = nodes;
        st.nodes_set  = true;
    }

    st.depth    = (depth == -1) ? MAX_PLY : depth;
    st.time_set = (st.tm.wtime != -1 || st.tm.btime != -1 || st.tm.movetime != -1);

    st.stopped   = false;
    st.print_uci = IsUci;

    thread_handler.start(st);
}

static void handle_setoption(std::istringstream& is) {
    std::string token, name, value;
    is >> std::skipws >> token;  // "name"
    if (token != "name") return;

    is >> std::skipws >> name;
    is >> std::skipws >> token;
    if (token == "value")
        is >> std::skipws >> value;
    else
        value.clear();

    if (name == "Hash" && !value.empty()) {
        try {
            current_hash_size = std::stoi(value);
        } catch (...) {
        }
        if (current_hash_size != prev_hash_size) {
            current_hash_size = std::min(current_hash_size, MAX_HASH_SIZE);
            prev_hash_size    = current_hash_size;
            table->Initialize(current_hash_size);
        }
        return;
    }

    auto set_int = [&](int& field) {
        if (!value.empty()) {
            try {
                field = std::stoi(value);
            } catch (...) {
            }
        }
    };
    auto set_float = [&](float& field) {
        if (!value.empty()) {
            try {
                field = std::stof(value);
            } catch (...) {
            }
        }
    };

    bool lmr_changed = false;
    if (name == "AspWindow") {
        set_int(SP.asp_window);
    } else if (name == "AspDivisor") {
        set_int(SP.asp_divisor);
    } else if (name == "AspDeltaDiv") {
        set_int(SP.asp_delta_div);
    } else if (name == "RfpMargin") {
        set_float(SP.rfp_margin);
    } else if (name == "RfpDepth") {
        set_int(SP.rfp_depth);
    } else if (name == "NmpBase") {
        set_float(SP.nmp_base);
    } else if (name == "NmpDivisor") {
        set_float(SP.nmp_divisor);
    } else if (name == "LmrBase") {
        set_float(SP.lmr_base);
        lmr_changed = true;
    } else if (name == "LmrDivisor") {
        set_float(SP.lmr_divisor);
        lmr_changed = true;
    } else if (name == "LmrMoveMin") {
        set_int(SP.lmr_move_min);
    } else if (name == "HistPrune") {
        set_int(SP.hist_prune);
    } else if (name == "HistBonusMul") {
        set_float(SP.hist_bonus_mul);
    }

    if (lmr_changed) init_search_tables();
}

void uci_loop() {
    printf("Lux %s Copyright (C) 2025 %s\n", VERSION, AUTHOR);

    ThreadHandler thread_handler;

    auto st     = std::make_unique<SearchThread>();
    auto ttable = std::make_unique<TranspositionTable>();

    table = ttable.get();
    table->Initialize(current_hash_size);

    std::string command;
    std::string token;

    while (std::getline(std::cin, command)) {
        std::istringstream is(command);

        token.clear();
        is >> std::skipws >> token;

        if (token == "stop") {
            st->stopped = true;
            thread_handler.stop();

        } else if (token == "quit") {
            st->stopped = true;
            thread_handler.stop();
            break;

        } else if (token == "isready") {
            std::cout << "readyok" << std::endl;

        } else if (token == "ucinewgame") {
            st->stopped = true;
            thread_handler.stop();
            table->Initialize(current_hash_size);
            st->tm.reset();
            st->time_set  = false;
            st->nodes_set = false;
            st->stopped   = false;
            st->set_fen(chess::constants::STARTPOS);

        } else if (token == "uci") {
            IsUci = true;
            uci_send_id();

        } else if (token == "position") {
            std::string option;
            is >> std::skipws >> option;
            if (option == "startpos") {
                st->set_fen(constants::STARTPOS);
            } else if (option == "fen") {
                std::string final_fen;
                for (int i = 0; i < 6; i++) {
                    is >> std::skipws >> option;
                    if (i > 0) final_fen.push_back(' ');
                    final_fen += option;
                }
                st->set_fen(final_fen);
            }
            is >> std::skipws >> option;
            if (option == "moves") {
                std::string moveString;
                while (is >> moveString) st->make_move(moveString);
            }

        } else if (token == "go") {
            handle_go(is, *st, thread_handler);

        } else if (token == "setoption") {
            handle_setoption(is);

            /* Debugging Commands */
        } else if (token == "print") {
            std::cout << st->board << std::endl;
        } else if (token == "eval") {
            std::cout << "Eval: " << evaluate(st->board) << std::endl;
        } else if (token == "repetition") {
            std::cout << st->board.isRepetition(1) << std::endl;
        } else if (token == "bench") {
            StartBenchmark(*st);
        } else if (token == "bencheval") {
            StartEvalBenchmark(*st);
        } else if (token == "spsa") {
            // Ints: c_end = max(value * 0.05, 0.5), r_end = 0.002
            // Floats: c_end = value * 0.05 (5%), r_end = 0.002
            auto int_c = [](int v) { return std::max(v * 0.05f, 0.5f); };
            printf("AspWindow,    int,   %d,    %d,    %d,    %.4f,  0.002\n", SP.asp_window,
                   (int)(SP.asp_window * SP_LO), (int)(SP.asp_window * SP_HI), int_c(SP.asp_window));
            printf("AspDivisor,   int,   %d, %d, %d, %.4f,  0.002\n", SP.asp_divisor, (int)(SP.asp_divisor * SP_LO),
                   (int)(SP.asp_divisor * SP_HI), int_c(SP.asp_divisor));
            printf("AspDeltaDiv,  int,   %d,    %d,    %d,    %.4f,  0.002\n", SP.asp_delta_div,
                   (int)(SP.asp_delta_div * SP_LO), (int)(SP.asp_delta_div * SP_HI), int_c(SP.asp_delta_div));
            printf("RfpMargin,    float, %.2f,  %.2f,  %.2f,  %.4f,  0.002\n", SP.rfp_margin, SP.rfp_margin * SP_LO,
                   SP.rfp_margin * SP_HI, SP.rfp_margin * 0.05f);
            printf("RfpDepth,     int,   %d,    %d,    %d,    %.4f,  0.002\n", SP.rfp_depth,
                   (int)(SP.rfp_depth * SP_LO), (int)(SP.rfp_depth * SP_HI), int_c(SP.rfp_depth));
            printf("NmpBase,      float, %.2f,  %.2f,  %.2f,  %.4f,  0.002\n", SP.nmp_base, SP.nmp_base * SP_LO,
                   SP.nmp_base * SP_HI, SP.nmp_base * 0.05f);
            printf("NmpDivisor,   float, %.2f,  %.2f,  %.2f,  %.4f,  0.002\n", SP.nmp_divisor, SP.nmp_divisor * SP_LO,
                   SP.nmp_divisor * SP_HI, SP.nmp_divisor * 0.05f);
            printf("LmrBase,      float, %.2f,  %.2f,  %.2f,  %.4f,  0.002\n", SP.lmr_base, SP.lmr_base * SP_LO,
                   SP.lmr_base * SP_HI, SP.lmr_base * 0.05f);
            printf("LmrDivisor,   float, %.2f,  %.2f,  %.2f,  %.4f,  0.002\n", SP.lmr_divisor, SP.lmr_divisor * SP_LO,
                   SP.lmr_divisor * SP_HI, SP.lmr_divisor * 0.05f);
            printf("LmrMoveMin,   int,   %d,    %d,    %d,    %.4f,  0.002\n", SP.lmr_move_min,
                   (int)(SP.lmr_move_min * SP_LO), (int)(SP.lmr_move_min * SP_HI), int_c(SP.lmr_move_min));
            printf("HistPrune,    int,   %d, %d, %d, %.4f,  0.002\n", SP.hist_prune, (int)(SP.hist_prune * SP_LO),
                   (int)(SP.hist_prune * SP_HI), int_c(SP.hist_prune));
            printf("HistBonusMul, float, %.2f,  %.2f,  %.2f,  %.4f,  0.002\n", SP.hist_bonus_mul,
                   SP.hist_bonus_mul * SP_LO, SP.hist_bonus_mul * SP_HI, SP.hist_bonus_mul * 0.05f);
        }
    }

    table->clear();
    std::cout << std::endl;
}