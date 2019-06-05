#include "ParserController.h"

ParserController::ParserController() {
}

ParserController::~ParserController() {
}

ParserController::ParserController(PDDLDriver *driver) {
    this->driver = driver;
}

// PRINT FUNCTIONS

/**
 * Print domain and problem data
 */
void ParserController::Print() {

    cout << endl;
    cout << "Domain:" << endl;
    cout << *(driver->domain) << endl;
    cout << "Problem:" << endl;
    cout << *(driver->problem) << endl;
}

/**
 * Print the domain predicates
 */
void ParserController::PrintPredicates() {
    cout << "Predicates:" << endl;
    vector<Predicate *> *predicates = driver->domain->getPredicates();
    for (auto it = predicates->begin(); it != predicates->end(); ++it)
        cout << *(*it) << endl;
    cout << endl;
}

/**
 * Print action
 */
void ParserController::PrintAction(Action action) {
    Predicate *predicate;
    cout << "Action: " << action.getName() << endl;
    cout << "Params: ";
    for (auto it = action.getParams()->begin(); it != action.getParams()->end(); ++it)
        cout << *it << " ";
    cout << endl << "Effects: " << endl;
    for (unsigned int i = 0; i < action.getEffects()->size(); i++) {
        predicate = action.getEffects()->at(i)->first;
        cout << predicate->getName() << " ";
        for (auto it = predicate->getArgs()->begin(); it != predicate->getArgs()->end(); ++it)
            cout << *it << " ";
        cout << action.getEffects()->at(i)->second << endl;
    }
    cout << "Preconditions: " << endl;
    for (unsigned int i = 0; i < action.getPrecond()->size(); i++) {
        predicate = action.getPrecond()->at(i)->first;
        cout << predicate->getName() << " ";
        for (auto it = predicate->getArgs()->begin(); it != predicate->getArgs()->end(); ++it)
            cout << *it << " ";
        cout << action.getPrecond()->at(i)->second << endl;
    }
    cout << endl;
}

/**
 * Print state
 */
void ParserController::PrintState(LiteralList state) {
    Predicate *predicate;
    for (unsigned int i = 0; i < state.size(); i++) {
        predicate = state.at(i)->first;
        cout << state.at(i)->first->getName() << " ";
        for (auto it = predicate->getArgs()->begin(); it != predicate->getArgs()->end(); ++it)
            cout << *it << " ";
        cout << state.at(i)->second << endl;
    }
    cout << endl;
}

// GET FUNCTIONS

/**
 *
 * @return vector with the domain predicates
 */
vector<Predicate *> ParserController::GetPredicates() {
    vector<Predicate *> predicates;
    for (unsigned int i = 0; i < driver->domain->getPredicates()->size(); i++) {
        predicates.push_back(driver->domain->getPredicates()->at(i));
    }
    return predicates;
}

/**
 *
 * @return vector with the domain actions
 */
vector<Action *> ParserController::GetActions() {
    vector<Action *> actions;
    for (unsigned int i = 0; i < driver->domain->getActions()->size(); i++) {
        actions.push_back(driver->domain->getActions()->at(i));
    }
    return actions;
}

/**
 *
 * @return LiteralList (=vector<Literal*>, Literal=pair<Predicate*,bool>) with the goal state
 */
LiteralList *ParserController::GetGoal() {
    return driver->problem->getGoal();
}

// UTILITIES

/**
 *
 * @return bool true if the action can be applied to the state, false otherwise
 */
vector<vector<string>> ParserController::IsApplicable(LiteralList *state, Action *action) {

    vector<vector<string>> parameterList;

    // Keep action parameters on a local vector of pair<paramName, value>
    vector<pair<string, string>> actionParams;
    for (unsigned int j = 0; j < action->getParams()->size(); j++) {
        pair<string, string> n;
        n.first = action->getParams()->at(j); // parameter name
        n.second = ""; // parameter value (not set)
        actionParams.push_back(n);
    }
    // Local list of this action's preconditions
    PreconditionList preconditions;
    for (unsigned int j = 0; j < action->getPrecond()->size(); j++) {

        // Creating a new pair of Predicate*, bool, to perform a deep-copy
        auto *newPredicatePair = new pair<Predicate *, bool>;
        auto *newArgList = new ArgumentList;
        auto *newArgStrList = new StringList;
//        TypeDict* newTypeDict; // TODO TypeDict is not deep copied over (not needed?)
        // Assign primitive values of this action precondition to arguments string list
        for (unsigned int i = 0; i < action->getPrecond()->at(j)->first->getArgs()->size(); i++) {
            newArgStrList->push_back(action->getPrecond()->at(j)->first->getArgs()->at(i));
        }
        // Assign arguments string list to ArgumentList which is used in predicates ctor
        newArgList->first = newArgStrList;

        // Call ctor of Predicate on first of predicate pair
        newPredicatePair->first = new Predicate(action->getPrecond()->at(j)->first->getName(), newArgList);

        // Assign primitive bool value of this action's precondition to the new predicate pair's second
        newPredicatePair->second = action->getPrecond()->at(j)->second;

        // Add the new predicate pair that is a deep copy of this action's precondition to the local preconditions list
        preconditions.push_back(newPredicatePair);

    }

    /*------------------------------------------------------------------------------------------------------------------
     * The following variables (n, i[n+1], etc.) plus the while loop and the nested while loop at the end
     * enables us to perform a dynamic number of nested loops.
     * It is used to try all the possible combinations of object assignment to variables.
     * The original comments are left as-they-were to help with readability (readability!? xD).
     * (found on https://stackoverflow.com/questions/9555864/variable-nested-for-loops)
    ------------------------------------------------------------------------------------------------------------------*/
    const int n = actionParams.size(); // Insert N here: how many loops do you need?
    int i[n + 1]; // if "n" is not known before hand, then this array will need to be created dynamically.
    //Note: there is an extra element at the end of the array, in order to keep track of whether to exit the array.

    for (int a = 0; a < n + 1; a++) {
        i[a] = 0;
    }

    int MAX = driver->problem->getObjects()->size(); //That's just an example, if all of the loops are
    // identical: e.g. "for(int i=0; i<79; i++)". If the value of MAX
    // changes for each loop, then make MAX an array instead: (new)
    // int MAX [n]; MAX[0]=10; MAX[1]=20;...;MAX[n-1]=whatever.

    int p = 0; //Used to increment all of the indices correctly, at the end of each loop.
    while (i[n] == 0) { //Remember, you're only using indices i[0], ..., i[n-1]. The (n+1)th index, i[n],
        // is just to check whether to the nested loop stuff has finished.

        //DO STUFF HERE. Pretend you're inside your nested for loops.
        // The more usual i,j,k,... have been replaced here with i[0], i[1], ..., i[n-1].

//        cout << "testing params:" << endl;
        for (unsigned int lvl = 0; lvl < actionParams.size(); lvl++) {
            actionParams.at(lvl).second = driver->problem->getObjects()->at(i[lvl]);
//            cout << actionParams.at(lvl).second << ", ";
        }
//        cout << endl;

        // Applying parameters to local preconditions
        for (unsigned int j = 0; j < preconditions.size(); j++) {
            for (unsigned int i = 0; i < preconditions.at(j)->first->getArgs()->size(); i++) {
                for (unsigned int z = 0; z < actionParams.size(); z++) {
                    if (preconditions.at(j)->first->getArgs()->at(i) == actionParams.at(z).first) {
                        preconditions.at(j)->first->getArgs()->at(i) = actionParams.at(z).second;
                    }
                }
            }
        }

        bool applicable = true;
        // Checking state for preconditions
        for (unsigned int j = 0; j < preconditions.size(); j++) {
            // Check for equality precondition
            if (preconditions.at(j)->first->getName() == "=") {
                if (preconditions.at(j)->second == 1) { // Equality true
                    bool allArgsEq = true;
                    for (unsigned int z = 0; z < preconditions.at(j)->first->getArgs()->size(); z++) {
                        for (unsigned int k = 0; k < preconditions.at(j)->first->getArgs()->size(); k++) {
                            if (z != k && preconditions.at(j)->first->getArgs()->at(z) !=
                                          preconditions.at(j)->first->getArgs()->at(k)) {
                                allArgsEq = false;
                            }
                        }
                    }
                    if (!allArgsEq) {
                        applicable = false;
//                        cout << "not applicable equality true failed" << endl;
                        break; // this breaks outer for
                    }
                } else { // Equality false
                    bool allArgsNotEq = true;
                    for (unsigned int z = 0; z < preconditions.at(j)->first->getArgs()->size(); z++) {
                        for (unsigned int k = 0; k < preconditions.at(j)->first->getArgs()->size(); k++) {
                            if (z != k && preconditions.at(j)->first->getArgs()->at(z) ==
                                          preconditions.at(j)->first->getArgs()->at(k)) {
                                allArgsNotEq = false;
                            }
                        }
                    }
                    if (!allArgsNotEq) {
                        applicable = false;
//                        cout << "not applicable equality false failed" << endl;
                        break; // this breaks outer for
                    }
                }
            }

            bool foundThisPrecond = false;
            for (unsigned int i = 0; i < state->size(); i++) {
                if (state->at(i)->first->getName() == preconditions.at(j)->first->getName()) {
                    bool sameParams = true;
                    for (unsigned int p = 0; p < state->at(i)->first->getArgs()->size(); p++) {
                        bool foundParam = false;
                        for (unsigned int z = 0; z < preconditions.at(j)->first->getArgs()->size(); z++) {
                            if (state->at(i)->first->getArgs()->at(p) == preconditions.at(j)->first->getArgs()->at(z)) {
                                foundParam = true;
                            }
                        }
                        if (!foundParam) sameParams = false;

                    }
                    if (sameParams) {
                        foundThisPrecond = true;
                        break; // Move on to next precondition
                    }
                }
            }
            // foundThisPrecond never turned true, which means we exhausted the state without finding this
            // precondition with the same arguments. Action is not applicable because the predicates bool is 1 (true)
            if (!foundThisPrecond && preconditions.at(j)->second == 1) {
                applicable = false;
//                cout << "not applicable didnt find precondition in state for these arguments" << endl;
                break;
            }
                // foundThisPrecond turned true, which means we found this precondition in the state with the same arguments.
                // Action is not applicable because the predicates bool is 0 (false, NOT)
            else if (foundThisPrecond && preconditions.at(j)->second == 0) {
                applicable = false;
//                cout << "not applicable found precondition in state for these arguments" << endl;
                break;
            }

        }

        if (applicable) {
            vector<string> params;
            for (unsigned int lvl = 0; lvl < actionParams.size(); lvl++) {
                params.push_back(actionParams.at(lvl).second);
            }
            parameterList.push_back(params);
        }

        // Reset applied objects to precondition parameters
        for (unsigned int j = 0; j < preconditions.size(); j++) {
            for (unsigned int i = 0; i < preconditions.at(j)->first->getArgs()->size(); i++) {
                preconditions.at(j)->first->getArgs()->at(i) = action->getPrecond()->at(j)->first->getArgs()->at(i);
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

    return parameterList;
}

/**
 *
 * @return vector containing pairs of applicable actions and their applicable params values on the state supplied
 */
vector<pair<Action *, vector<vector<string>>>> ParserController::ApplicableActions(LiteralList *state) {

    vector<Action *> actions = this->GetActions();
    vector<pair<Action *, vector<vector<string>>>> applicableActions;
    for (unsigned int i = 0; i < actions.size(); i++) {
        pair<Action *, vector<vector<string>>> applicableActionsParams;
        applicableActionsParams.first = actions.at(i);
        applicableActionsParams.second = this->IsApplicable(state, actions.at(i));
        if (!applicableActionsParams.second.empty()) applicableActions.push_back(applicableActionsParams);
    }
    return applicableActions;
}

/**
 *
 * @return the new state after the action is applied to the provided state
 */
LiteralList *ParserController::NextState(LiteralList *state, Action action, vector<string> param_values) {

    Predicate *state_predicate;
    Predicate *effect_predicate;
    Predicate *precondition_predicate;
    bool effect_status;
    bool state_predicate_status;

    LiteralList *new_state = new LiteralList();
    for(unsigned int i=0; i<state->size(); i++) {
        Literal* literal = new Literal();
        literal->second = state->at(i)->second;
        literal->first = state->at(i)->first;
        new_state->emplace_back(literal);
    }

    // Keep action parameters on a local HashMap
    map<string, string> action_params;
    for (unsigned int i = 0; i < action.getParams()->size(); i++) {
        // Create HashMap entry with key the param name, and value its value
        action_params[action.getParams()->at(i)] = param_values.at(i);
    }

    // Keep precondition parameters on a local HashMap
    map<string, string> precond_params;
    for (unsigned int precond_index = 0; precond_index < action.getPrecond()->size(); precond_index++) {
        precondition_predicate = action.getPrecond()->at(precond_index)->first;

        // Search in state for the predicate that satisfies this precondition
        for (unsigned int state_index = 0; state_index < new_state->size(); state_index++) {
            Predicate *state_predicate = new_state->at(state_index)->first;
            // Compare precondition and state predicates names
            if (!precondition_predicate->getName().compare(state_predicate->getName()))
                // If their names are the same, check their bool values
                if (action.getPrecond()->at(precond_index)->second == new_state->at(state_index)->second) {
                    // Assign to each parameter the value of the state predicate
                    for (unsigned int index = 0; index < precondition_predicate->getArgs()->size(); index++) {
                        precond_params[precondition_predicate->getArgs()->at(index)] = state_predicate->getArgs()->at(
                                index);
                    }
                }
        }
    }

    bool applied;
    unsigned int state_size = state->size();
    // For each action effect, check if it appears in the state predicates
    for (unsigned int effects_index = 0;
         effects_index < action.getEffects()->size(); effects_index++) { // Loop through action's effects
        // Assign current effect predicate value and status to the local variables
        effect_predicate = action.getEffects()->at(effects_index)->first;
        effect_status = action.getEffects()->at(effects_index)->second;

        // Set applied to false as this effect has not been applied yet
        applied = false;

        // Find all state predicates that appear in the action's effect
        unsigned int state_index = 0;
        while (state_index < state_size && !applied) {
            // Assign current state predicate value to state_predicate
            state_predicate = state->at(state_index)->first;
            state_predicate_status = state->at(state_index)->second;

            // Compare effect name with state predicate name
            if (!effect_predicate->getName().compare(state_predicate->getName())) // returns 0 when equal
            {
                if (state_predicate_status != effect_status) {
                    // Different status between this state predicate and the effect

                    // Check if the parameters match
                    unsigned int correct_args = 0;
                    for (unsigned int arg_index = 0; arg_index < state_predicate->getArgs()->size(); arg_index++) {
                        string param = effect_predicate->getArgs()->at(arg_index);

                        if (!precond_params[param].compare(state_predicate->getArgs()->at(arg_index))) {
                            // State predicate has the correct value for this parameter, increment counter
                            correct_args++;
                        }
                    }


                    // Check if all the state predicate arguments match the effects arguments
                    if (correct_args == state_predicate->getArgs()->size()) {
                        // Apply effect
                        new_state->at(state_index)->second = action.getEffects()->at(effects_index)->second;

                        // Flag applied
                        applied = true;
                    }
                }
            }
            state_index++;
        }

        // Check if the effect was applied in this state
        if (!applied) {
            // The effect adds a new literal to the state
            Literal *new_literal = new Literal();
            new_literal->first = effect_predicate;
            for (unsigned int i = 0; i < effect_predicate->getArgs()->size(); i++) {
                for (map<string, string>::iterator action = action_params.begin();
                     action != action_params.end(); ++action) {

                    if (!effect_predicate->getArgs()->at(i).compare(action->first))
                        new_literal->first->getArgs()->at(i) = action->second;
                }
            }
            new_literal->second = effect_status;
            new_state->emplace_back(new_literal);
            //delete (new_literal);
        }
    }

    return new_state;
}

vector<LiteralList *> ParserController::NextStates(LiteralList *state, Action action, vector<vector<string>> param_values) {

    vector<LiteralList *> states;// = vector<LiteralList *>();
    LiteralList * new_state;

    for(unsigned int i=0; i<param_values.size(); i++) {
        states = vector<LiteralList *>();
        LiteralList * new_state = NextState(state, action, param_values.at(i));
        states.emplace_back(new_state);
        //PrintState(*new_state);
    }

    return states;
}




