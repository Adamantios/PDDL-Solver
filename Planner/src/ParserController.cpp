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
    vector<Predicate*> *predicates = driver->domain->_predicates;
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
    for (unsigned int i=0; i< driver->domain->_predicates->size(); i++) {
        predicates.push_back(driver->domain->_predicates->at(i));
    }
    return predicates;
}

/**
 *
 * @return vector with the domain actions
 */
vector<Action *> ParserController::GetActions() {
    vector<Action*> actions;
    for (unsigned int i=0; i< driver->domain->_actions->size(); i++) {
        actions.push_back(driver->domain->_actions->at(i));
    }
    return actions;
}





