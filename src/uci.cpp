#include "uci.h"

#include "bench.h"
#include "eval.h"
#include "spsa.h"
#include "thread.h"

using namespace chess;

int current_hash_size = DEFAULT_HASH_SIZE;
int prev_hash_size    = current_hash_size;

bool is_uci = false;

TranspositionTable* table;

static void uci_send_id() {
    printf("id name Lux %s\n", VERSION);
    printf("id author %s\n", AUTHOR);

    printf("option name Hash type spin default %d min %d max %d\n", DEFAULT_HASH_SIZE, MIN_HASH_SIZE, MAX_HASH_SIZE);
    printf("option name Threads type spin default 1 min 1 max %d\n", MAX_THREADS);

    print_uci_options();

    std::cout << "uciok" << std::endl;
}

static void handle_go(std::istringstream& is, SearchThread& st, ThreadHandler& thread_handler) {
    std::string token;
    is >> std::skipws >> token;

    st.tm.reset();

    int depth = -1;

    while (token != "none") {
        if (token == "infinite") {
            depth = -1;
            break;
        }

        if (token == "movestogo") {
            is >> std::skipws >> token;
            st.tm.movestogo = std::stoi(token);
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
            st.tm.node_limit = std::stoi(token);
        }

        if (!(is >> std::skipws >> token)) break;
    }

    st.depth = (depth == -1) ? MAX_PLY : depth;

    st.stopped   = false;
    st.print_uci = is_uci;

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

    set_uci_option(name, value);
}

void uci_loop() {
    printf("Lux %s Copyright (C) 2026 %s\n", VERSION, AUTHOR);

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
            st->stopped = false;
            st->set_fen(chess::constants::STARTPOS);

        } else if (token == "uci") {
            is_uci = true;
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
            print_spsa_csv();
        }
    }

    table->clear();
    std::cout << std::endl;
}