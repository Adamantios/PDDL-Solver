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

    ParserController(PDDLDriver *driver);

    virtual ~ParserController();

    // FUNCTIONS
    // Prints
    void Print();

    void PrintPredicates();

    void PrintAction(Action action);

    void PrintState(LiteralList state);

    // Gets
    vector<Predicate *> GetPredicates();

    vector<Action *> GetActions();

    LiteralList *GetGoal();

    // Utilities
    vector<pair<Action *, vector<vector<string>>>> ApplicableActions(LiteralList *currentState);

    LiteralList *NextState(LiteralList *state, Action action, vector<string> param_values);

    vector<LiteralList *>NextStates(LiteralList *state, Action* action, vector<vector<string>> param_values);

private:
    // FUNCTIONS
    // Utilities
    vector<vector<string>> IsApplicable(LiteralList *state, Action *action);
};


#endif //PDDL_SOLVER_PARSERCONTROLLER_H
