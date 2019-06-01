#include "heuristics.h"

Heuristics::Heuristics(LiteralList *goal) : _goal(goal) {}

DeltaMap Heuristics::init_delta_values(LiteralList *current_state) {
    DeltaMap delta_map;

    // Iterate through state literals.
    for (Literal *state_literal : *current_state) {
        // Get current state_literal's predicate and logical part.
        Predicate *state_predicate = state_literal->first;
        bool state_logical_part = state_literal->second;
        std::cout << "Current: " << *state_literal->first << std::endl;

        // Create iterator, to define if any of the goal's literals matches the state_literal.
        auto iterator = find_if(_goal->begin(), _goal->end(),
                                [&](const Literal *literal) -> bool {
                                    // No need to compare types. Two identical PDDL objects cannot have different types.
                                    return literal->first->_name == state_predicate->_name &&
                                           *literal->first->_args == *state_predicate->_args &&
                                           literal->second == state_logical_part;
                                });

        // Insert zero if goal exists at the current state, otherwise infinity.
        delta_map.insert({state_predicate, (iterator != _goal->end() ? 0 : std::numeric_limits<double>::infinity())});
    }

    return delta_map;
}

DeltaMap Heuristics::delta_max(LiteralList *current_state) {
    // Initialize Delta values.
    DeltaMap delta_map = init_delta_values(current_state);

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
