#ifndef PDDL_SOLVER_HEURISTICS_H
#define PDDL_SOLVER_HEURISTICS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <problem.hh>
#include "predicate.hh"
#include "action.hh"

// Predicates mapped with their costs.
typedef std::unordered_map<Predicate *, int> DeltaMap;

class Heuristics {
private:
    LiteralList *_goal;

public:
    explicit Heuristics(LiteralList *goal);

    DeltaMap init_delta_values(LiteralList *current_state);

    std::unordered_map<Predicate *, int> delta_max(LiteralList *current_state);
};


#endif //PDDL_SOLVER_HEURISTICS_H
