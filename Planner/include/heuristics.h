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

    DeltaMap _delta_map{};

    static LiteralList::iterator FindLiteral(LiteralList *state, Literal *literal);

    void InitDeltaValues(LiteralList *current_state);

    static double MaxCost(DeltaValues *deltas);

    static double AdditiveCost(DeltaValues *deltas);

    double GetDelta(Literal *literal);

    DeltaValues GetDeltas(const LiteralList *literal_list);

    void EstimateDeltaValues(LiteralList *current_state, Method method);

public:
    explicit Heuristics(ParserController *controller);

    double Estimate(LiteralList *current_state, Method method = MAX_COST);
};


#endif //PDDL_SOLVER_HEURISTICS_H
