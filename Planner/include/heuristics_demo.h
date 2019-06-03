#ifndef PDDL_SOLVER_HEURISTICS_DEMO_H
#define PDDL_SOLVER_HEURISTICS_DEMO_H


#include "heuristics.h"

class HeuristicsDemo {
public:
    HeuristicsDemo(ParserController parserController, LiteralList *currentState);

private:
    static void RevealEstimations(const DeltaMap &estimations);
};


#endif //PDDL_SOLVER_HEURISTICS_DEMO_H
