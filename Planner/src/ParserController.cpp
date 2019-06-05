#include "ParserController.h"

ParserController::ParserController() {
}

ParserController::~ParserController() {
}

ParserController::ParserController(PDDLDriver* driver) {
    this->driver = driver;
}

// PRINT FUNCTIONS

/**
 * Print domain and problem data
 */
void ParserController::Print() {

    cout << endl;
    cout << "Domain:" <<endl;
    cout << *(driver->domain)  << endl;
    cout << "Problem:" <<endl;
    cout << *(driver->problem) << endl;
}

/**
 * Print the domain predicates
 */
void ParserController::PrintPredicates() {
    cout << "Predicates:" <<endl;
    vector<Predicate*> *predicates = driver->domain->getPredicates();
    for (auto it = predicates->begin(); it != predicates->end(); ++it)
        cout << *(*it) << endl;
}

// GET FUNCTIONS

/**
 *
 * @return vector with the domain predicates
 */
vector<Predicate *> ParserController::GetPredicates() {
    vector<Predicate*> predicates;
    for (unsigned int i=0; i< driver->domain->getPredicates()->size(); i++) {
        predicates.push_back(driver->domain->getPredicates()->at(i));
    }
    return predicates;
}

/**
 *
 * @return vector with the domain actions
 */
vector<Action*> ParserController::GetActions() {
    vector<Action*> actions;
    for (unsigned int i=0; i< driver->domain->getActions()->size(); i++) {
        actions.push_back(driver->domain->getActions()->at(i));
    }
    return actions;
}

/**
 *
 * @return LiteralList (=vector<Literal*>, Literal=pair<Predicate*,bool>) with the goal state
 */
LiteralList* ParserController::GetGoal(){
    return driver->problem->getGoal();
}

// UTILITIES

/**
 *
 * @return bool true if the action can be applied to the state, false otherwise
 */
vector<vector<string>> ParserController::IsApplicable(LiteralList* state, Action* action) {

    vector<vector<string>> parameterList;

    // Keep action parameters on a local vector of pair<paramName, value>
    vector<pair<string, string>> actionParams;
    for (unsigned int j = 0; j < action->getParams()->size(); j++) {
        pair<string,string> n;
        n.first = action->getParams()->at(j); // parameter name
        n.second = ""; // parameter value (not set)
        actionParams.push_back(n);
    }
    // Local list of this action's preconditions
    PreconditionList preconditions;
    for (unsigned int j = 0; j < action->getPrecond()->size(); j++) {

        // Creating a new pair of Predicate*, bool, to perform a deep-copy
        auto* newPredicatePair = new pair<Predicate*, bool>;
        auto* newArgList = new ArgumentList;
        auto* newArgStrList = new StringList;
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
    int i[n+1]; // if "n" is not known before hand, then this array will need to be created dynamically.
    //Note: there is an extra element at the end of the array, in order to keep track of whether to exit the array.

    for (int a=0; a<n+1; a++) {
        i[a]=0;
    }

    int MAX = driver->problem->getObjects()->size(); //That's just an example, if all of the loops are
                                                     // identical: e.g. "for(int i=0; i<79; i++)". If the value of MAX
                                                     // changes for each loop, then make MAX an array instead: (new)
                                                     // int MAX [n]; MAX[0]=10; MAX[1]=20;...;MAX[n-1]=whatever.

    int p = 0; //Used to increment all of the indices correctly, at the end of each loop.
    while (i[n]==0) { //Remember, you're only using indices i[0], ..., i[n-1]. The (n+1)th index, i[n],
                      // is just to check whether to the nested loop stuff has finished.

        //DO STUFF HERE. Pretend you're inside your nested for loops.
        // The more usual i,j,k,... have been replaced here with i[0], i[1], ..., i[n-1].

//        cout << "testing params:" << endl;
        for(unsigned int lvl = 0; lvl < actionParams.size(); lvl++) {
            actionParams.at(lvl).second = driver->problem->getObjects()->at(i[lvl]);
//            cout << actionParams.at(lvl).second << ", ";
        }
//        cout << endl;

        // Applying parameters to local preconditions
        for (unsigned int j = 0; j < preconditions.size(); j++) {
            for (unsigned int i = 0; i < preconditions.at(j)->first->getArgs()->size(); i++) {
                for (unsigned int z = 0; z < actionParams.size(); z++) {
                    if (preconditions.at(j)->first->getArgs()->at(i) == actionParams.at(z).first){
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
                                          preconditions.at(j)->first->getArgs() ->at(k)) {
                                allArgsEq = false;
                            }
                        }
                    }
                    if (!allArgsEq) {
                        applicable = false;
//                        cout << "not applicable equality true failed" << endl;
                        break; // this breaks outer for
                    }
                }
                else { // Equality false
                    bool allArgsNotEq = true;
                    for (unsigned int z = 0; z < preconditions.at(j)->first->getArgs()->size(); z++) {
                        for (unsigned int k = 0; k < preconditions.at(j)->first->getArgs()->size(); k++) {
                            if (z != k && preconditions.at(j)->first->getArgs()->at(z) ==
                                          preconditions.at(j)->first->getArgs() ->at(k)) {
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
                            if (state->at(i)->first->getArgs()->at(p) == preconditions.at(j)->first->getArgs()->at(z)){
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
            for(unsigned int lvl = 0; lvl < actionParams.size(); lvl++) {
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
        while(i[p]==MAX) { //(or "MAX[p]" if each "for" loop is different. Note that from an English point
                           // of view, this is more like "if(i[p]==MAX". (Initially i[0]) If this is true, then i[p]
                           // is reset to 0, and i[p+1] is incremented.
            i[p]=0;
            i[++p]++; //increase p by 1, and increase the next (p+1)th index
            if(i[p]!=MAX)
                p=0; //Alternatively, "p=0" can be inserted above (currently commented-out). This one's more
                     // efficient though, since it only resets p when it actually needs to be reset!
        }
    }

    return parameterList;
}

/**
 *
 * @return vector containing pairs of applicable actions and their applicable params values on the state supplied
 */
vector<pair<Action*, vector<vector<string>>>> ParserController::ApplicableActions(LiteralList* state) {

    vector<Action*> actions = this->GetActions();
    vector<pair<Action*, vector<vector<string>>>> applicableActions;
    for (unsigned int i = 0; i < actions.size(); i++) {
        pair<Action*, vector<vector<string>>> applicableActionsParams;
        applicableActionsParams.first = actions.at(i);
        applicableActionsParams.second = this->IsApplicable(state, actions.at(i));
        if (!applicableActionsParams.second.empty()) applicableActions.push_back(applicableActionsParams);
    }
    return applicableActions;
}




