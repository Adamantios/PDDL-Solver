#ifndef PDDL_SOLVER_HEURISTICS_H
#define PDDL_SOLVER_HEURISTICS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <problem.hh>
#include "predicate.hh"
#include "action.hh"
#include "ParserController.h"

// Literals mapped with their costs.
typedef std::unordered_map<Literal *, int> DeltaMap;
typedef vector<int> DeltaValues;

enum Method {
    MAX_COST, ADDITIVE_COST
};

class Heuristics {
private:
    ParserController *_controller;

    DeltaMap InitDeltaValues(LiteralList *current_state);

    static int MaxCost(DeltaValues *preconditions_deltas);

    static int AdditiveCost(DeltaValues *preconditions_deltas);

public:
    explicit Heuristics(ParserController *controller);

    DeltaMap EstimateDeltaValues(LiteralList *current_state, Method method = MAX_COST);
};


#endif //PDDL_SOLVER_HEURISTICS_H
