#ifndef PDDL_SOLVER_PARSERCONTROLLER_H
#define PDDL_SOLVER_PARSERCONTROLLER_H

#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"
#include <iostream>

using namespace std;

class ParserController {

    // TODO create Hash and Decode methods.
    //  Move non relative methods to a new class called 'Utils' or something like that.

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

    void PrintAction(Action *action);

    void PrintState(LiteralList state);

    // Gets
    vector<Predicate *> GetPredicates();

    vector<Action *> GetActions();

    LiteralList *GetGoal();

    // Utilities
    vector<Action *> *ApplicableActions(LiteralList *currentState);

    LiteralList *NextState(LiteralList *state, Action action);

    vector<LiteralList *> NextStates(LiteralList *state, vector<Action *>* actions);

    static bool LiteralsEqual(Literal *literal1, Literal *literal2);

    static LiteralList::iterator FindLiteral(LiteralList *state, Literal *literal);

private:
    // FUNCTIONS
    // Utilities
    vector<vector<string>> IsApplicable(LiteralList *state, Action *action);

    static LiteralList *UnrollLiteralList(const LiteralList *rolled_list, const StringList *rolled_params,
                                          ParameterList *unrolled_params);

    static vector<Action *> *UnrollActions(vector<pair<Action *, vector<vector<string>>>> *rolled_actions);
};


#endif //PDDL_SOLVER_PARSERCONTROLLER_H
