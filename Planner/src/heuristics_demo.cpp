#include <heuristics_demo.h>

HeuristicsDemo::HeuristicsDemo(Utils utils, LiteralList *currentState) {
    // Max-Cost.
    Heuristics heuristics = Heuristics(&utils);
    double estimation = heuristics.Estimate(currentState);
    std::cout << "Estimation using Max-Cost is: " << estimation << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    // Additive-Cost.
    heuristics = Heuristics(&utils, ADDITIVE_COST);
    estimation = heuristics.Estimate(currentState);
    std::cout << "Estimation using Additive-Cost is: " << estimation << std::endl;
}
