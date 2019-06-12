#include <heuristics_demo.h>

HeuristicsDemo::HeuristicsDemo(ParserController parserController, LiteralList *currentState) {
    // Max-Cost.
    Heuristics heuristics = Heuristics(&parserController);
    double estimation = heuristics.Estimate(currentState);
    std::cout << "Estimation using Max-Cost is: " << estimation << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    // Additive-Cost.
    heuristics = Heuristics(&parserController, ADDITIVE_COST);
    estimation = heuristics.Estimate(currentState);
    std::cout << "Estimation using Additive-Cost is: " << estimation << std::endl;
}
