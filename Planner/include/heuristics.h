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

// Predicates mapped with their costs.
typedef std::unordered_map<Predicate *, int> DeltaMap;

class Heuristics {
private:
    ParserController *_controller;

public:
    explicit Heuristics(ParserController *controller);

    DeltaMap InitDeltaValues(LiteralList *current_state);

    std::unordered_map<Predicate *, int> DeltaMax(LiteralList *current_state);
};


#endif //PDDL_SOLVER_HEURISTICS_H
