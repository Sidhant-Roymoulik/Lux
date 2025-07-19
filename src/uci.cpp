#include "uci.h"

#include "bench.h"
#include "eval.h"
#include "thread.h"

using namespace chess;

int current_hash_size = DEFAULT_HASH_SIZE;
int prev_hash_size    = current_hash_size;

bool IsUci  = false;
bool TUNING = false;

TranspositionTable *table;

static void uci_send_id() {
    printf("id name Lux %s\n", VERSION);
    printf("id author %s\n", AUTHOR);

    printf("option name Hash type spin default %d min %d max %d\n", DEFAULT_HASH_SIZE, MIN_HASH_SIZE, MAX_HASH_SIZE);
    printf("option name Threads type spin default 1 min 1 max %d\n", MAX_THREADS);

    std::cout << "uciok" << std::endl;
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
            continue;

        } else if (token == "ucinewgame") {
            table->Initialize(current_hash_size);
            continue;

        } else if (token == "uci") {
            IsUci = true;
            uci_send_id();
            continue;
        }

        /* Handle UCI position command */
        else if (token == "position") {
            std::string option;
            is >> std::skipws >> option;
            if (option == "startpos") {
                st->set_fen(constants::STARTPOS);
            } else if (option == "fen") {
                std::string final_fen;
                is >> std::skipws >> option;
                final_fen = option;

                // Record side to move
                final_fen.push_back(' ');
                is >> std::skipws >> option;
                final_fen += option;

                // Record castling
                final_fen.push_back(' ');
                is >> std::skipws >> option;
                final_fen += option;

                // record enpassant square
                final_fen.push_back(' ');
                is >> std::skipws >> option;
                final_fen += option;

                // record fifty move conter
                final_fen.push_back(' ');
                is >> std::skipws >> option;
                final_fen += option;

                final_fen.push_back(' ');
                is >> std::skipws >> option;
                final_fen += option;

                // Finally, apply the fen.
                st->set_fen(final_fen);
            }
            is >> std::skipws >> option;
            if (option == "moves") {
                std::string moveString;

                while (is >> moveString) {
                    st->make_move(moveString);
                }
            }
            continue;
        }

        /* Handle UCI go command */
        else if (token == "go") {
            is >> std::skipws >> token;

            // Initialize variables
            int depth = -1;

            int64_t nodes = -1;

            while (token != "none") {
                if (token == "infinite") {
                    depth = -1;
                    break;
                }
                if (token == "movestogo") {
                    is >> std::skipws >> token;
                    st->tm.movestogo = stoi(token);
                    is >> std::skipws >> token;
                    continue;
                }

                // Depth
                if (token == "depth") {
                    is >> std::skipws >> token;
                    depth = std::stoi(token);
                    is >> std::skipws >> token;
                    continue;
                }

                // Time
                if (token == "wtime") {
                    is >> std::skipws >> token;
                    st->tm.wtime = std::stod(token);
                    is >> std::skipws >> token;
                    continue;
                }
                if (token == "btime") {
                    is >> std::skipws >> token;
                    st->tm.btime = std::stod(token);
                    is >> std::skipws >> token;
                    continue;
                }

                // Increment
                if (token == "winc") {
                    is >> std::skipws >> token;
                    st->tm.winc = std::stod(token);
                    is >> std::skipws >> token;
                    continue;
                }
                if (token == "binc") {
                    is >> std::skipws >> token;
                    st->tm.binc = std::stod(token);
                    is >> std::skipws >> token;
                    continue;
                }

                if (token == "movetime") {
                    is >> std::skipws >> token;
                    st->tm.movetime = stod(token);
                    is >> std::skipws >> token;
                    continue;
                }
                if (token == "nodes") {
                    is >> std::skipws >> token;
                    nodes = stoi(token);
                    is >> std::skipws >> token;
                }
                token = "none";
            }

            if (nodes != -1) {
                st->node_limit = nodes;
                st->nodes_set  = true;
            }

            st->depth = depth;
            if (st->tm.wtime != -1 || st->tm.btime != -1 || st->tm.movetime != -1) {
                st->time_set = true;
            }

            if (depth == -1) {
                st->depth = MAX_PLY;
            }

            st->stopped   = false;
            st->print_uci = IsUci;

            thread_handler.start(*st);
        }

        else if (token == "setoption") {
            // Parse: setoption name <name> [value <value>]
            std::string name, value;
            is >> std::skipws >> token;  // should be "name"
            if (token == "name") {
                is >> std::skipws >> name;
                // Optionally parse "value"
                is >> std::skipws >> token;
                if (token == "value") {
                    is >> std::skipws >> value;
                } else {
                    value.clear();
                }

                if (name == "Hash" && !value.empty()) {
                    try {
                        current_hash_size = std::stoi(value);
                    } catch (...) {
                        // ignore invalid value
                    }
                    if (current_hash_size != prev_hash_size) {
                        current_hash_size = std::min(current_hash_size, MAX_HASH);
                        prev_hash_size    = current_hash_size;
                        table->Initialize(current_hash_size);
                    }
                }
            }
        }

        /* Debugging Commands */
        else if (token == "print") {
            std::cout << st->board << std::endl;
        } else if (token == "eval") {
            std::cout << "Eval: " << evaluate(st->board) << std::endl;
        } else if (token == "repetition") {
            std::cout << st->board.isRepetition(1) << std::endl;
        } else if (token == "bench") {
            StartBenchmark(*st);
        } else if (token == "bencheval") {
            StartEvalBenchmark(*st);
        }
    }
    table->clear();

    std::cout << std::endl;
}