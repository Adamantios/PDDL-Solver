#ifndef PDDL_SOLVER_PARSERCONTROLLER_H
#define PDDL_SOLVER_PARSERCONTROLLER_H

#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"
#include <iostream>

using namespace std;

class ParserController {

protected:
    // VARIABLES
    PDDLDriver *driver;

public:
    // CONSTRUCTORS
    ParserController();
    ParserController(PDDLDriver* driver);
    virtual ~ParserController();

    // FUNCTIONS
    void Print();
    void PrintPredicates();

    vector<Predicate*> GetPredicates();
    vector<Action*> GetActions();

};


#endif //PDDL_SOLVER_PARSERCONTROLLER_H
