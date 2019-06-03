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

    DeltaMap *_delta_map{};

    static LiteralList::iterator FindLiteral(LiteralList *state, Literal *literal);

    void InitDeltaValues(LiteralList *current_state);

    DeltaValues GetPreconditionsDeltas(Action *action);

    static double MaxCost(DeltaValues *preconditions_deltas);

    static double AdditiveCost(DeltaValues *preconditions_deltas);

public:

    explicit Heuristics(ParserController *controller);

    double GetDelta(Literal *literal);

    DeltaMap *EstimateDeltaValues(LiteralList *current_state, Method method = MAX_COST);
};


#endif //PDDL_SOLVER_HEURISTICS_H
