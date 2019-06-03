#include <heuristics_demo.h>

HeuristicsDemo::HeuristicsDemo(ParserController parserController, LiteralList *currentState) {
    Heuristics heuristics = Heuristics(&parserController);

    DeltaMap estimations = heuristics.EstimateDeltaValues(currentState);
    std::cout << "Delta map estimations using Max-Cost contain:" << std::endl;
    RevealEstimations(estimations);

    std::cout << "--------------------------------------------------" << std::endl;

    estimations = heuristics.EstimateDeltaValues(currentState, ADDITIVE_COST);
    std::cout << "Delta map estimations using Additive-Cost contain:" << std::endl;
    RevealEstimations(estimations);
}

void HeuristicsDemo::RevealEstimations(const DeltaMap &estimations) {
    for (auto &estimation : estimations) {
        std::cout << estimation.first->first->getName() << "(";
        for (auto &arg : *estimation.first->first->getArgs()) {
            std::cout << arg;
            if (arg != estimation.first->first->getArgs()->back()) printf(", ");
        }

        std::cout << ")" << ": " << estimation.second << std::endl;
    }
}
