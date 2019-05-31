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

    // TODO private bool is_applicable(LiteralList state, Action action) -> return if the action can be applied to the state.

    // TODO public vector<Actions> applicable_actions(LiteralList state) -> use GetActions and is_applicable
    //  to return all the actions which can be applied to the state.

    // TODO public LiteralList get_goal() -> return the goal.
    //  see problem.hh for "LiteralList".

    vector<Predicate*> GetPredicates();
    vector<Action*> GetActions();

};


#endif //PDDL_SOLVER_PARSERCONTROLLER_H
