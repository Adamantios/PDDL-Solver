#include "heuristics.h"

Heuristics::Heuristics(ParserController *controller, EstimationMethod method) :
        _controller(controller),
        _estimation_method(method == MAX_COST ? MaxCost : AdditiveCost) {}

/**
 * Compares two literals.
 * @param literal1 the first literal.
 * @param literal2 the second literal.
 * @return bool
 */
bool Heuristics::LiteralsEqual(Literal *literal1, Literal *literal2) {
    // TODO move function to ParserController maybe?

    // No need to compare types since identical PDDL objects cannot have different types.
    return literal1->first->getName() == literal2->first->getName() &&
           *literal1->first->getArgs() == *literal2->first->getArgs() &&
           literal1->second == literal2->second;
}

/**
 * Finds a literal in a state.
 * @param state the state to be searched.
 * @param literal the literal to search for.
 * @return iterator.
 */
LiteralList::iterator Heuristics::FindLiteral(LiteralList *state, Literal *literal) {
    // TODO move function to ParserController maybe?

    auto iterator = find_if(state->begin(), state->end(),
                            [&](Literal *state_literal) -> bool {
                                /*
                                 * Lambda compares two literals.
                                 */
                                return LiteralsEqual(state_literal, literal);
                            });

    return iterator;
}

/**
 * Initializes the Delta Values of the current state.
 * @param current_state the current state.
 */
void Heuristics::InitDeltaValues(LiteralList *current_state) {
    // Initialize every state literal with 0.
    for (Literal *state_literal : *current_state)
        _delta_map.insert({state_literal, 0});
}

/**
 * Gets the delta value of a literal.
 * @param literal the literal to get the value from.
 * @return the delta value.
 */
double Heuristics::GetDelta(Literal *literal) {
    // Search delta.
    for (auto const &delta_pair : _delta_map)
        // If found return it.
        if (LiteralsEqual(literal, delta_pair.first))
            return delta_pair.second;

    // If not found return infinity.
    return std::numeric_limits<double>::infinity();
}

/**
 * Gets the delta values of a state.
 * @param literal_list the state to get the values from.
 * @return the delta values.
 */
DeltaValues *Heuristics::GetDeltas(const LiteralList *literal_list) {
    auto *deltas = new DeltaValues();

    // Get delta for each precondition.
    for (Literal *literal : *literal_list)
        deltas->push_back(GetDelta(literal));

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
        vector<pair<Action *, vector<vector<string>>>> applicable_actions =
                _controller->ApplicableActions(&relaxed_state);

        // For each unrolled applicable action.
        for (Action *action : *UnrollActions(&applicable_actions)) {
            // Get action's preconditions delta values.
            DeltaValues *preconditions_deltas = GetDeltas(action->getFilteredPrecond());
            // Set action's cost to 1.
            double action_cost = 1;

            // For each action's effect.
            for (Literal *effect : *action->getEffects()) {
                // If the effect is not in the relaxed state.
                if (FindLiteral(&relaxed_state, effect) == relaxed_state.end()) {
                    // Relaxed state hasn't leveled off since an effect can be added.
                    leveled_off = false;
                    // Add the current effect to the relaxed state.
                    relaxed_state.push_back(effect);
                }

                // Get effect's delta value.
                double effect_delta = GetDelta(effect);
                // Estimate the current action's cost, based on the method.
                double cost = _estimation_method(preconditions_deltas);
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
    DeltaValues *goal_deltas = GetDeltas(_controller->GetGoal());

    // Estimate and return the goal's cost, based on the method.
    return _estimation_method(goal_deltas);
}

LiteralList *Heuristics::UnrollLiteralList(const LiteralList *rolled_list, const StringList *rolled_params,
                                           ParameterList *unrolled_params) {
    // TODO move function to ParserController maybe?

    auto unrolled_list = new LiteralList();

    // For each literal of the rolled list.
    for (Literal *literal : *rolled_list) {
        auto args = new ArgumentList({new StringList(), new TypeDict()});

        // For each literal's argument.
        for_each(literal->first->getArgs()->begin(), literal->first->getArgs()->end(),
                /*
                 * Lambda stores the unrolled parameter which corresponds to the rolled of the literal, as an argument.
                 */
                 [&](string arg) -> void {
                     // Find argument in the rolled parameters.
                     auto iterator = std::find(rolled_params->begin(), rolled_params->end(), arg);
                     // Get its index.
                     int index = std::distance(rolled_params->begin(), iterator);
                     // Store the unrolled parameter corresponding to the index found as an argument.
                     args->first->push_back(unrolled_params->first->at(index));
                 });

        // Create a predicate from the arguments that where found.
        auto predicate = new Predicate(literal->first->getName(), args);
        // Store the predicate with its logical part to the unrolled list.
        unrolled_list->push_back(new Literal({predicate, literal->second}));
    }

    return unrolled_list;
}

vector<Action *> *Heuristics::UnrollActions(vector<pair<Action *, vector<vector<string>>>> *applicable_actions) {
    // TODO move function to ParserController maybe?

    auto *unrolled_actions = new vector<Action *>();

    // Fore each rolled action.
    for (const pair<Action *, vector<vector<string>>> &rolled_action : *applicable_actions)
        // For each parameter combination of the action.
        for (const StringList &assigned_params : rolled_action.second) {
            // Get rolled parameters.
            const StringList *rolled_params = rolled_action.first->getParams();

            // Initialize unrolled parameters, preconditions and effects.
            auto params = new ParameterList(new StringList(assigned_params), nullptr);
            PreconditionList *preconditions = UnrollLiteralList(rolled_action.first->getPrecond(), rolled_params,
                                                                params);
            auto effects = UnrollLiteralList(rolled_action.first->getEffects(), rolled_params, params);

            // Create an action from the unrolled parameters, preconditions and effects.
            auto *action = new Action(rolled_action.first->getName(), params, preconditions, effects);
            // Store the action.
            unrolled_actions->push_back(action);
        }

    return unrolled_actions;
}
