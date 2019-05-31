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
    // Prints
    void Print();
    void PrintPredicates();

    // Gets
    vector<Predicate*> GetPredicates();
    vector<Action*> GetActions();
    LiteralList* GetGoal();

    // Utilities
    vector<Action*> ApplicableActions(LiteralList* currentState);

private:
    // FUNCTIONS
    // Utilities
    bool IsApplicable(LiteralList* state, Action action);

};


#endif //PDDL_SOLVER_PARSERCONTROLLER_H
