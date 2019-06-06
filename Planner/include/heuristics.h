#ifndef PDDL_SOLVER_HEURISTICS_H
#define PDDL_SOLVER_HEURISTICS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <problem.hh>
#include "predicate.hh"
#include "action.hh"
#include "ParserController.h"

// Literals mapped with their costs.
typedef std::unordered_map<Literal *, double> DeltaMap;
typedef vector<double> DeltaValues;

enum EstimationMethod {
    MAX_COST, ADDITIVE_COST
};

class Heuristics {
private:
    ParserController *_controller;
    std::function<double(DeltaValues *deltas)> _estimation_method;
    DeltaMap _delta_map{};

    static bool LiteralsEqual(Literal *literal1, Literal *literal2);

    static LiteralList::iterator FindLiteral(LiteralList *state, Literal *literal);

    void InitDeltaValues(LiteralList *current_state);

    static double MaxCost(DeltaValues *deltas);

    static double AdditiveCost(DeltaValues *deltas);

    double GetDelta(Literal *literal);

    DeltaValues *GetDeltas(const LiteralList *literal_list);

    void EstimateDeltaValues(LiteralList *current_state);

    static LiteralList *UnrollLiteralList(const LiteralList *rolled_list, const StringList *rolled_params,
                                          ParameterList *unrolled_params);

    static vector<Action *> *UnrollActions(vector<pair<Action *, vector<vector<string>>>> *applicable_actions);

public:
    explicit Heuristics(ParserController *controller, EstimationMethod method = MAX_COST);

    double Estimate(LiteralList *current_state);
};


#endif //PDDL_SOLVER_HEURISTICS_H
