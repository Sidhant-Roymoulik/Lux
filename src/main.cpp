#include <iostream>

#include "search.h"
#include "uci.h"

int main(int argv, char **argc) {
    init_search_tables();
    uci_loop(argv, argc);

    return 0;
}