#include "heuristics.h"

Heuristics::Heuristics(ParserController *controller, EstimationMethod method) :
        _controller(controller),
        _estimation_method(method == MAX_COST ? MaxCost : AdditiveCost) {}

/**
 * Finds a literal in a state.
 * @param state the state to be searched.
 * @param literal the literal to search for.
 * @return iterator.
 */
LiteralList::iterator Heuristics::FindLiteral(LiteralList *state, Literal *literal) {
    // TODO move function to ParserController maybe?

    // Get literal's predicate and logical part.
    Predicate *predicate = literal->first;
    bool logical_part = literal->second;

    auto iterator = find_if(state->begin(), state->end(),
                            [&](const Literal *literal) -> bool {
                                /*
                                 * Lambda compares two literals.
                                 * No need to compare types since identical PDDL objects cannot have different types.
                                 */
                                return literal->first->getName() == predicate->getName() &&
                                       literal->first->getArgs() == predicate->getArgs() &&
                                       literal->second == logical_part;
                            });

    return iterator;
}

/**
 * Initializes the Delta Values of the current state.
 * @param current_state the current state.
 */
void Heuristics::InitDeltaValues(LiteralList *current_state) {
    LiteralList *goal = _controller->GetGoal();

    // Iterate through state literals.
    for (Literal *state_literal : *current_state) {
        // Search if any of the goal's literals matches the state_literal.
        auto iterator = FindLiteral(goal, state_literal);
        // Insert zero if goal exists at the current state, otherwise infinity.
        _delta_map.insert({state_literal, (iterator != goal->end() ? 0 : std::numeric_limits<double>::infinity())});
    }
}

/**
 * Gets the delta value of a literal.
 * @param literal the literal to get the value from.
 * @return the delta value.
 */
double Heuristics::GetDelta(Literal *literal) {
    double effect_delta;

    // Search delta.
    auto iterator = _delta_map.find(literal);
    if (iterator != _delta_map.end())
        // If found store it.
        effect_delta = iterator->second;
    else
        // If not set it with infinity.
        effect_delta = std::numeric_limits<double>::infinity();

    return effect_delta;
}

/**
 * Gets the delta values of a state.
 * @param literal_list the state to get the values from.
 * @return the delta values.
 */
DeltaValues Heuristics::GetDeltas(const LiteralList *literal_list) {
    DeltaValues deltas = DeltaValues();

    // Get delta for each precondition.
    for (Literal *literal : *literal_list)
        deltas.push_back(GetDelta(literal));

    return deltas;
}

/**
 * Applies the Max-Cost rule.
 * @param deltas the deltas for which the rule will be applied.
 * @return the resulting cost.
 */
double Heuristics::MaxCost(DeltaValues *deltas) {
    return *max_element(deltas->begin(), deltas->end());
}

/**
 * Applies the Additive-Cost rule.
 * @param deltas the deltas for which the rule will be applied.
 * @return the resulting cost.
 */
double Heuristics::AdditiveCost(DeltaValues *deltas) {
    double deltas_sum = 0;
    for (auto &delta : *deltas)
        deltas_sum += delta;

    return deltas_sum;
}

/**
 * Estimates the delta values.
 * @param current_state the state for which the delta values will be estimated.
 * @return the delta values mapped with the corresponding literals.
 */
void Heuristics::EstimateDeltaValues(LiteralList *current_state) {
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
            DeltaValues preconditions_deltas = GetDeltas(action->getPrecond());
            // Set action's cost to 1.
            double action_cost = 1;

            for (Literal *effect : *action->getEffects()) {
                // If the effect is not in the relaxed state.
                if (FindLiteral(&relaxed_state, effect) != relaxed_state.end()) {
                    // Relaxed state hasn't leveled off since an effect can be added.
                    leveled_off = false;
                    // Add the current effect to the relaxed state.
                    relaxed_state.push_back(effect);
                }

                // Get effect's delta value.
                double effect_delta = GetDelta(effect);
                // Estimate the current action's cost, based on the method.
                double cost = _estimation_method(&preconditions_deltas);
                // Calculate the current effect's delta value.
                double delta_value = min(effect_delta, action_cost + cost);
                // Store the delta value.
                _delta_map.insert({effect, delta_value});
            }
        }
    } while (!leveled_off);
}

/**
 * Estimates the delta value for a state.
 * @param current_state the state for which the delta value will be estimated.
 * @return the delta value.
 */
double Heuristics::Estimate(LiteralList *current_state) {
    // Estimate the Delta Map.
    EstimateDeltaValues(current_state);
    // Get delta for each goal literal.
    DeltaValues goal_deltas = GetDeltas(_controller->GetGoal());

    // Estimate and return the goal's cost, based on the method.
    return _estimation_method(&goal_deltas);
}
