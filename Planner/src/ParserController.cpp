
#include <iostream>
#include "ParserController.h"

using namespace std;


ParserController::ParserController() {
}

ParserController::~ParserController() {
}

ParserController::ParserController(PDDLDriver* driver) {
    this->driver = driver;
}


void ParserController::Print() {

    cout << endl;
    cout << "Domain:" <<endl;
    cout << *(driver->domain)  << endl;
    cout << "Problem:" <<endl;
    cout << *(driver->problem) << endl;
}

void ParserController::PrintPredicates() {
    cout << "Predicates:" <<endl;
    vector<Predicate*> *predicates = driver->domain->_predicates;
    for (unsigned int i=0; i< predicates->size(); i++) {
        cout << *(predicates->at(i)) << endl;
    }
}


