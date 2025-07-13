#include "eval.h"
#include "search.h"
#include "uci.h"

int main() {
    init_search_tables();
    init_eval_tables();

    uci_loop();

    return 0;
}