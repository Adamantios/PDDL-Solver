#include "utils.h"

Utils::Utils() = default;

Utils::~Utils() = default;

Utils::Utils(PDDLDriver *driver) {
    this->driver_ = driver;
}

// GET FUNCTIONS

/**
 *
 * @return vector with the domain actions
 */
vector<Action *> Utils::GetActions() {
    vector<Action *> actions;
    for (auto action : *driver_->domain->getActions()) {
        actions.push_back(action);
    }
    return actions;
}

/**
 *
 * @return LiteralList (=vector<Literal*>, Literal=pair<Predicate*,bool>) with the goal state
 */
LiteralList *Utils::GetGoal() {
    return driver_->problem->getGoal();
}

// UTILITIES

/**
 *
 * @return bool true if the action can be applied to the state, false otherwise
 */
vector<vector<string>> Utils::IsApplicable(LiteralList *state, Action *action) {

    vector<vector<string>> parameter_list;

    // Keep action parameters on a local vector of pair<paramName, value>
    vector<pair<string, string>> action_params;
    for (const auto &param : *action->getParams()) {
        pair<string, string> n;
        n.first = param; // parameter name
        n.second = ""; // parameter value (not set)
        action_params.push_back(n);
    }
    // Local list of this action's preconditions
    PreconditionList preconditions;
    for (auto action_preconditions : *action->getPrecond()) {
        // Creating a new pair of Predicate*, bool, to perform a deep-copy
        auto *new_predicate_pair = new pair<Predicate *, bool>;
        auto *new_arg_list = new ArgumentList;
        auto *new_arg_str_list = new StringList;

        // Assign primitive values of this action precondition to arguments string list
        for (const auto &precondition : *action_preconditions->first->getArgs()) {
            new_arg_str_list->push_back(precondition);
        }
        // Assign arguments string list to ArgumentList which is used in predicates ctor
        new_arg_list->first = new_arg_str_list;

        // Call ctor of Predicate on first of predicate pair
        new_predicate_pair->first = new Predicate(action_preconditions->first->getName(), new_arg_list);

        // Assign primitive bool value of this action's precondition to the new predicate pair's second
        new_predicate_pair->second = action_preconditions->second;

        // Add the new predicate pair that is a deep copy of this action's precondition to the local preconditions list
        preconditions.push_back(new_predicate_pair);

    }

    /*------------------------------------------------------------------------------------------------------------------
     * The following variables (n, i[n+1], etc.) plus the while loop and the nested while loop at the end
     * enables us to perform a dynamic number of nested loops.
     * It is used to try all the possible combinations of object assignment to variables.
     * The original comments are left as-they-were to help with readability (readability!? xD).
     * (found on https://stackoverflow.com/questions/9555864/variable-nested-for-loops)
    ------------------------------------------------------------------------------------------------------------------*/
    const int n = action_params.size(); // Insert N here: how many loops do you need?
    int i[n + 1]; // if "n" is not known before hand, then this array will need to be created dynamically.
    //Note: there is an extra element at the end of the array, in order to keep track of whether to exit the array.

    for (int a = 0; a < n + 1; a++) {
        i[a] = 0;
    }

    int MAX = driver_->problem->getObjects()->size(); //That's just an example, if all of the loops are
    // identical: e.g. "for(int i=0; i<79; i++)". If the value of MAX
    // changes for each loop, then make MAX an array instead: (new)
    // int MAX [n]; MAX[0]=10; MAX[1]=20;...;MAX[n-1]=whatever.

    int p = 0; //Used to increment all of the indices correctly, at the end of each loop.
    while (i[n] == 0) { //Remember, you're only using indices i[0], ..., i[n-1]. The (n+1)th index, i[n],
        // is just to check whether to the nested loop stuff has finished.

        //DO STUFF HERE. Pretend you're inside your nested for loops.
        // The more usual i,j,k,... have been replaced here with i[0], i[1], ..., i[n-1].

        for (unsigned int lvl = 0; lvl < action_params.size(); lvl++) {
            action_params.at(lvl).second = driver_->problem->getObjects()->at(i[lvl]);
        }

        // Applying parameters to local preconditions
        for (auto &precondition : preconditions) {
            for (auto &arg : *precondition->first->getArgs()) {
                for (auto &action_param : action_params) {
                    if (arg == action_param.first) {
                        arg = action_param.second;
                    }
                }
            }
        }

        bool applicable = true;
        // Checking state for preconditions
        for (auto &precondition : preconditions) {
            // Check for equality precondition
            if (precondition->first->getName() == "=") {
                if (precondition->second == 1) { // Equality true
                    bool all_args_eq = true;
                    for (unsigned int z = 0; z < precondition->first->getArgs()->size(); z++) {
                        for (unsigned int k = 0; k < precondition->first->getArgs()->size(); k++) {
                            if (z != k && precondition->first->getArgs()->at(z) !=
                                          precondition->first->getArgs()->at(k)) {
                                all_args_eq = false;
                            }
                        }
                    }
                    if (!all_args_eq) {
                        applicable = false;
                        break; // this breaks outer for
                    }
                } else { // Equality false
                    bool all_args_not_eq = true;
                    for (unsigned int z = 0; z < precondition->first->getArgs()->size(); z++) {
                        for (unsigned int k = 0; k < precondition->first->getArgs()->size(); k++) {
                            if (z != k && precondition->first->getArgs()->at(z) ==
                                          precondition->first->getArgs()->at(k)) {
                                all_args_not_eq = false;
                            }
                        }
                    }
                    if (!all_args_not_eq) {
                        applicable = false;
                        break; // this breaks outer for
                    }
                }
            }

            bool found_this_precondition = false;
            bool same_boolean = false;
            for (auto &literal : *state) {
                if (literal->first->getName() == precondition->first->getName()) {
                    bool same_params = true;
                    for (const auto &literal_arguments : *literal->first->getArgs()) {
                        bool found_param = false;
                        for (const auto &precondition_arguments : *precondition->first->getArgs()) {
                            if (literal_arguments == precondition_arguments) {
                                found_param = true;
                            }
                        }
                        if (!found_param) same_params = false;

                    }
                    if (same_params) {
                        found_this_precondition = true;
                        same_boolean = literal->second == precondition->second;
                        break; // Move on to next precondition
                    }
                }
            }
            // found_this_precondition never turned true, which means we exhausted the state without finding this
            // precondition with the same arguments. Action is not applicable because the predicates bool is 1 (true)
            if (!found_this_precondition && precondition->second == 1) {
                applicable = false;
                break;
            }
                // found_this_precondition turned true, which means we found this precondition in the state with the same arguments.
                // Action is not applicable if the precondition was found in this state and the boolean parameters do not match
            else if (found_this_precondition && !same_boolean) {
                applicable = false;
                break;
            }

        }

        if (applicable) {
            vector<string> params;
            for (auto &action_param : action_params) {
                params.push_back(action_param.second);
            }
            parameter_list.push_back(params);
        }

        // Reset applied objects to precondition parameters
        for (unsigned int outer = 0; outer < preconditions.size(); outer++) {
            for (unsigned int inner = 0; inner < preconditions.at(outer)->first->getArgs()->size(); inner++) {
                preconditions.at(outer)->first->getArgs()->at(inner) = action->getPrecond()->at(
                        outer)->first->getArgs()->at(inner);
            }
        }

        //Now, after you've done your stuff, we need to increment all of the indices correctly.
        i[0]++;
        // p = 0;//Commented out, because it's replaced by a more efficient alternative below.
        while (i[p] == MAX) { //(or "MAX[p]" if each "for" loop is different. Note that from an English point
            // of view, this is more like "if(i[p]==MAX". (Initially i[0]) If this is true, then i[p]
            // is reset to 0, and i[p+1] is incremented.
            i[p] = 0;
            i[++p]++; //increase p by 1, and increase the next (p+1)th index
            if (i[p] != MAX)
                p = 0; //Alternatively, "p=0" can be inserted above (currently commented-out). This one's more
            // efficient though, since it only resets p when it actually needs to be reset!
        }
    }

    return parameter_list;
}

/**
 *
 * @return vector containing pairs of applicable actions and their applicable params values on the state supplied
 */
vector<Action *> *Utils::ApplicableActions(LiteralList *current_state) {

    vector<Action *> actions = this->GetActions();
    vector<pair<Action *, vector<vector<string>>>> applicable_actions;

    for (auto &action : actions) {
        pair<Action *, vector<vector<string>>> applicable_actions_params;
        applicable_actions_params.first = action;
        applicable_actions_params.second = this->IsApplicable(current_state, action);
        if (!applicable_actions_params.second.empty()) applicable_actions.push_back(applicable_actions_params);
    }

    return UnrollActions(&applicable_actions);
}

/**
 *
 * @return the new state after the action is applied to the provided state
 */
LiteralList *Utils::NextState(LiteralList *state, Action *action) {
    Predicate *state_predicate;
    Predicate *effect_predicate;
    bool effect_status;

    // Copy given state to new_state variable
    auto *new_state = new LiteralList();
    for (auto &state_literal : *state) {
        auto *literal = new Literal();
        literal->second = state_literal->second;
        literal->first = state_literal->first;
        new_state->emplace_back(literal);
    }

    bool applied;
    unsigned int state_size = state->size();
    // For each action effect, check if it appears in the state predicates
    for (auto effects_index : *action->getEffects()) { // Loop through action's effects
        // Assign current effect predicate value and status to the local variables
        effect_predicate = effects_index->first;
        effect_status = effects_index->second;

        // Set applied to false as this effect has not been applied yet
        applied = false;

        // Find all state predicates that appear in the action's effect
        unsigned int state_index = 0;
        while (state_index < state_size && !applied) {
            // Assign current state predicate value to state_predicate
            state_predicate = state->at(state_index)->first;

            // Compare effect name with state predicate name
            if (effect_predicate->getName() == state_predicate->getName()) {
                // Check if the parameters match
                unsigned int correct_args = 0;
                for (unsigned int arg_index = 0; arg_index < state_predicate->getArgs()->size(); arg_index++) {
                    string param = effect_predicate->getArgs()->at(arg_index);
                    if (param == state_predicate->getArgs()->at(arg_index))
                        // State predicate has the correct value for this parameter, increment counter
                        correct_args++;
                }

                // Check if all the state predicate arguments match the effects arguments
                if (correct_args == state_predicate->getArgs()->size()) {
                    // Apply effect
                    new_state->at(state_index)->second = effects_index->second;

                    // Flag applied
                    applied = true;
                }
            }
            state_index++;
        }

        // Check if the effect was applied in this state
        if (!applied) {
            // The effect adds a new literal to the state
            auto *new_literal = new Literal();
            new_literal->first = effect_predicate;
            new_literal->second = effect_status;
            new_state->emplace_back(new_literal);
        }
    }

    return new_state;
}

/**
 * Compares two literals.
 * @param literal_1 the first literal.
 * @param literal_2 the second literal.
 * @return bool
 */
bool Utils::LiteralsEqual(Literal *literal_1, Literal *literal_2) {
    // No need to compare types since identical PDDL objects cannot have different types.
    return literal_1->first->getName() == literal_2->first->getName() &&
           *literal_1->first->getArgs() == *literal_2->first->getArgs() &&
           literal_1->second == literal_2->second;
}

/**
 * Finds a literal in a state.
 * @param state the state to be searched.
 * @param literal the literal to search for.
 * @return iterator.
 */
LiteralList::iterator Utils::FindLiteral(LiteralList *state, Literal *literal) {
    auto iterator = find_if(state->begin(), state->end(),
                            [&](Literal *state_literal) -> bool {
                                /*
                                 * Lambda compares two literals.
                                 */
                                return LiteralsEqual(state_literal, literal);
                            });

    return iterator;
}

LiteralList *Utils::UnrollLiteralList(const LiteralList *rolled_list, const StringList *rolled_params,
                                      ParameterList *unrolled_params) {
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

vector<Action *> *Utils::UnrollActions(vector<pair<Action *, vector<vector<string>>>> *rolled_actions) {
    auto *unrolled_actions = new vector<Action *>();

    // Fore each rolled action.
    for (const pair<Action *, vector<vector<string>>> &rolled_action : *rolled_actions)
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
