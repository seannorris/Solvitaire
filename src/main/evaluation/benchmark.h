//
// Created by thecharlesblake on 4/5/18.
//

#ifndef SOLVITAIRE_BENCHMARK_H
#define SOLVITAIRE_BENCHMARK_H


#include "../game/sol_rules.h"

class benchmark {
public:
    static void run(const sol_rules &rules, uint64_t);
};


#endif //SOLVITAIRE_BENCHMARK_H