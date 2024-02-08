#include "eval.h"
#include "search.h"
#include "uci.h"

int main(int argv, char **argc) {
    init_search_tables();
    init_eval_tables();

    uci_loop(argv, argc);

    return 0;
}