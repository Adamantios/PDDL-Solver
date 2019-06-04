#include "heuristics.h"

Heuristics::Heuristics(ParserController *controller) : _controller(controller) {}

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
                                       *literal->first->getArgs() == *predicate->getArgs() &&
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
        _delta_map->insert({state_literal, (iterator != goal->end() ? 0 : std::numeric_limits<int>::infinity())});
    }
}

/**
 * Gets the delta value of a literal.
 * @param literal the literal to get the value from.
 * @return the delta value.
 */
int Heuristics::GetDelta(Literal *literal) {
    int effect_delta;

    // Search delta.
    auto iterator = _delta_map->find(literal);
    if (iterator != _delta_map->end())
        // If found store it.
        effect_delta = iterator->second;
    else
        // If not set it with infinity.
        effect_delta = std::numeric_limits<int>::infinity();

    return effect_delta;
}

/**
 * Gets the delta values of an action's preconditions.
 * @param action the action for which the preconditions delta values will be retrieved.
 * @return the delta values.
 */
DeltaValues Heuristics::GetPreconditionsDeltas(Action *action) {
    DeltaValues preconditions_deltas = DeltaValues();

    // Get delta for each precondition.
    for (Literal *literal : *action->getPrecond())
        preconditions_deltas.push_back(GetDelta(literal));

    return preconditions_deltas;
}

/**
 * Applies the Max-Cost rule.
 * @param preconditions_deltas the preconditions deltas.
 * @return the cost.
 */
int Heuristics::MaxCost(DeltaValues *preconditions_deltas) {
    return *max_element(preconditions_deltas->begin(), preconditions_deltas->end());
}

/**
 * Applies the Additive-Cost rule.
 * @param preconditions_deltas the preconditions deltas.
 * @return the cost.
 */
int Heuristics::AdditiveCost(DeltaValues *preconditions_deltas) {
    int deltas_sum = 0;
    for (auto &delta : *preconditions_deltas)
        deltas_sum += delta;

    return deltas_sum;
}

/**
 * Estimates the delta values.
 * @param current_state the state for which the delta values will be estimated.
 * @param method the method to be used.
 * @return the delta values mapped with the corresponding literals.
 */
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
                // If the effect is not in the relaxed state.
                if (FindLiteral(&relaxed_state, effect) != relaxed_state.end()) {
                    // Relaxed state hasn't leveled off since an effect can be added.
                    leveled_off = false;
                    // Add the current effect to the relaxed state.
                    relaxed_state.push_back(effect);
                }

                // Get effect's delta value.
                int effect_delta = GetDelta(effect);
                // Estimate the current action's cost, based on the method.
                int cost = method == MAX_COST ? MaxCost(&preconditions_deltas) : AdditiveCost(&preconditions_deltas);
                // Calculate the current effect's delta value.
                int delta_value = min(effect_delta, action_cost + cost);
                // Store the delta value.
                _delta_map->insert({effect, delta_value});
            }
        }
    } while (!leveled_off);

    return _delta_map;
}
