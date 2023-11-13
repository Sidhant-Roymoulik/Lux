#pragma once

#include "search.h"

struct EvalInfo {
    int gamephase = 0;
    Score score;
};

void init_eval_tables();
int evaluate(SearchThread& st);