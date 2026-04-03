#include "bench.h"
#include "eval.h"
#include "search.h"
#include "uci.h"

int main(int argc, char* argv[]) {
    init_search_tables();
    init_eval_tables();

    if (argc > 1 && std::string(argv[1]) == "bench") {
        TranspositionTable ttable;
        SearchThread st;
        table = &ttable;
        table->Initialize(64);
        StartBenchmark(st);
        return 0;
    }

    uci_loop();

    return 0;
}