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
typedef std::unordered_map<Literal *, double> DeltaMap;
typedef vector<double> DeltaValues;

enum Method {
    MAX_COST, ADDITIVE_COST
};

class Heuristics {
private:
    ParserController *_controller;

    DeltaMap InitDeltaValues(LiteralList *current_state);

    static double MaxCost(DeltaValues *preconditions_deltas);

    static double AdditiveCost(DeltaValues *preconditions_deltas);

    static DeltaValues GetPreconditionsDeltas(Action *action, DeltaMap *delta_map);
// TODO create _delta_map.
public:

    explicit Heuristics(ParserController *controller);

    DeltaMap EstimateDeltaValues(LiteralList *current_state, Method method = MAX_COST);

    static double GetLiteralDelta(Literal *literal, DeltaMap *delta_map);
};


#endif //PDDL_SOLVER_HEURISTICS_H
