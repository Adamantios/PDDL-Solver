#include "heuristics.h"

Heuristics::Heuristics(ParserController *controller) : _controller(controller) {}

void Heuristics::InitDeltaValues(LiteralList *current_state) {
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
        _delta_map->insert({state_literal, (iterator != goal->end() ? 0 : std::numeric_limits<double>::infinity())});
    }
}

double Heuristics::GetDelta(Literal *literal) {
    double effect_delta;

    // Search delta.
    auto iterator = _delta_map->find(literal);
    if (iterator != _delta_map->end())
        // If found store it.
        effect_delta = iterator->second;
    else
        // If not set it with infinity.
        effect_delta = std::numeric_limits<double>::infinity();

    return effect_delta;
}

DeltaValues Heuristics::GetPreconditionsDeltas(Action *action) {
    DeltaValues preconditions_deltas = DeltaValues();

    // Get delta for each precondition.
    for (Literal *literal : *action->getPrecond())
        preconditions_deltas.push_back(GetDelta(literal));

    return preconditions_deltas;
}

double Heuristics::MaxCost(DeltaValues *preconditions_deltas) {
    return *max_element(preconditions_deltas->begin(), preconditions_deltas->end());
}

double Heuristics::AdditiveCost(DeltaValues *preconditions_deltas) {
    double deltas_sum = 0;
    for (auto &delta : *preconditions_deltas)
        deltas_sum += delta;

    return deltas_sum;
}

DeltaMap *Heuristics::EstimateDeltaValues(LiteralList *current_state, Method method) {
    // Initialize Delta values.
    InitDeltaValues(current_state);

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
            // Get action's preconditions delta values.
            DeltaValues preconditions_deltas = GetPreconditionsDeltas(action);
            // Set action's cost to 1.
            int action_cost = 1;

            for (Literal *effect : *action->getEffects()) {
                // Relaxed state hasn't leveled off since an effect can be added.
                leveled_off = false;
                // Add the current effect to the relaxed state.
                relaxed_state.push_back(effect);
                // Get effect's delta value, if it exists. Otherwise set it with infinity.
                double effect_delta = GetDelta(effect);
                // Estimate the current action's cost, based on the method.
                double cost = method == MAX_COST ? MaxCost(&preconditions_deltas) : AdditiveCost(&preconditions_deltas);
                // Calculate the current effect's delta value.
                double delta_value = min(effect_delta, action_cost + cost);
                // Store the delta value.
                _delta_map->insert({effect, delta_value});
            }
        }
    } while (!leveled_off);

    return _delta_map;
}
