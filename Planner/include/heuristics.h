#ifndef PDDL_SOLVER_HEURISTICS_H
#define PDDL_SOLVER_HEURISTICS_H

#include "action.hh"
#include "plan_utils.h"
#include "predicate.hh"
#include <algorithm>
#include <functional>
#include <iostream>
#include <problem.hh>
#include <unordered_map>
#include <vector>

// Literals mapped with their costs.
typedef std::unordered_map<Literal*, double> DeltaMap;
typedef std::vector<double> DeltaValues;

enum EstimationMethod {
    MAX_COST,
    ADDITIVE_COST
};

class Heuristics {
private:
    Utils* utils_;
    std::function<double(DeltaValues* deltas)> estimation_method_;
    DeltaMap delta_map_ {};

    explicit Heuristics(Utils* utils, std::function<double(DeltaValues* deltas)> estimation_method);

    void InitDeltaValues(LiteralList* current_state);

    static double MaxCost(DeltaValues* deltas);

    static double AdditiveCost(DeltaValues* deltas);

    double GetDelta(Literal* literal);

    DeltaValues* GetDeltas(const LiteralList* literal_list);

    void EstimateDeltaValues(LiteralList* current_state);

public:
    explicit Heuristics(Utils* utils, EstimationMethod method = ADDITIVE_COST);

    double Estimate(LiteralList* current_state);
};

#endif // PDDL_SOLVER_HEURISTICS_H
