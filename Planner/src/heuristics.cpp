#include "heuristics.h"

Heuristics::Heuristics(ParserController *controller) : _controller(controller) {}

DeltaMap Heuristics::InitDeltaValues(LiteralList *current_state) {
    DeltaMap delta_map;
    LiteralList *goal = _controller->GetGoal();

    // Iterate through state literals.
    for (Literal *state_literal : *current_state) {
        // Get current state_literal's predicate and logical part.
        Predicate *state_predicate = state_literal->first;
        bool state_logical_part = state_literal->second;
        std::cout << "Current: " << *state_literal->first << std::endl;

        // Create iterator, to define if any of the goal's literals matches the state_literal.
        auto iterator = find_if(goal->begin(), goal->end(),
                                [&](const Literal *literal) -> bool {
                                    // No need to compare types. Two identical PDDL objects cannot have different types.
                                    return literal->first->getName() == state_predicate->getName() &&
                                           *literal->first->getArgs() == *state_predicate->getArgs() &&
                                           literal->second == state_logical_part;
                                });

        // Insert zero if goal exists at the current state, otherwise infinity.
        delta_map.insert({state_literal, (iterator != goal->end() ? 0 : std::numeric_limits<double>::infinity())});
    }

    return delta_map;
}

DeltaMap Heuristics::EstimateDeltaValues(LiteralList *current_state, Method method) {
    // Initialize Delta values.
    DeltaMap delta_map = InitDeltaValues(current_state);

    // // Define a relaxed set and a flag which marks changes in it.
    // LiteralList relaxed_set;
    // bool set_updated;
    //
    // // Loop until U does not change.
    // do {
    //     // Get applicable actions.
    //     std::vector<Action *> applicable_actions = parserController.ApplicableActions(current_state);
    //     // Update flag.
    //     set_updated = condition ? true : false;
    // } while (set_updated);

    return delta_map;
}
