#include <heuristics_demo.h>

HeuristicsDemo::HeuristicsDemo(ParserController parserController, LiteralList *currentState) {
    Heuristics heuristics = Heuristics(&parserController);

    double estimation = heuristics.Estimate(currentState);
    std::cout << "Estimation using Max-Cost is: " << estimation << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    estimation = heuristics.Estimate(currentState, ADDITIVE_COST);
    std::cout << "Estimation using Additive-Cost is: " << estimation << std::endl;
}
