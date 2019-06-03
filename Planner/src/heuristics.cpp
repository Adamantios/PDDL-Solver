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

int Heuristics::MaxCost(DeltaValues *preconditions_deltas) {
    return *max_element(preconditions_deltas->begin(), preconditions_deltas->end());
}

int Heuristics::AdditiveCost(DeltaValues *preconditions_deltas) {
    int sum = 0;
    for (auto &n : *preconditions_deltas)
        sum += n;

    return sum;
}

DeltaMap Heuristics::EstimateDeltaValues(LiteralList *current_state, Method method) {
    // Initialize Delta values.
    DeltaMap delta_map = InitDeltaValues(current_state);

    // Initialize a relaxed state, using the current state and a flag which marks if it has leveled off.
    LiteralList relaxed_state(*current_state);
    bool leveled_off;

    // Loop until relaxed state does not change.
    do {
        // Reset flag.
        leveled_off = true;
        // Get applicable actions.
        std::vector<Action *> applicable_actions = _controller->ApplicableActions(&relaxed_state);

        // For each action's effect.
        for (Action *action : applicable_actions) {
            for (Literal *effect : *action->getEffects()) {
                // Relaxed state hasn't leveled off since an effect can be added.
                leveled_off = false;
                // Add the current effect to the relaxed state.
                relaxed_state.push_back(effect);
                // TODO Get effect's delta value.
                int prev_delta = 0;
                // TODO Get action's preconditions delta values.
                DeltaValues preconditions_deltas = DeltaValues(0, 0);
                // Set action's cost to 1.
                int action_cost = 1;
                // Estimate the current action's cost, based on the method.
                int cost = method == MAX_COST ? MaxCost(&preconditions_deltas) : AdditiveCost(&preconditions_deltas);
                // Calculate the current effect's delta value.
                int delta_value = min(prev_delta, action_cost + cost);
                // Store the delta value.
                delta_map.insert({effect, delta_value});
            }
        }
    } while (!leveled_off);

    return delta_map;
}
