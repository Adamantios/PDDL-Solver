#ifndef PDDL_SOLVER_UTILS_H
#define PDDL_SOLVER_UTILS_H

#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"
#include <iostream>

using namespace std;

class Utils {
protected:
    // VARIABLES
    PDDLDriver *driver_{};

public:
    // CONSTRUCTORS
    Utils();

    explicit Utils(PDDLDriver *driver);

    virtual ~Utils();

    // FUNCTIONS
    // Gets

    vector<Action *> GetActions();

    LiteralList *GetGoal();

    // Utilities

    vector<Action *> *ApplicableActions(LiteralList *current_state);

    static LiteralList *NextState(LiteralList *state, Action *action);

    static bool LiteralsEqual(Literal *literal_1, Literal *literal_2);

    static LiteralList::iterator FindLiteral(LiteralList *state, Literal *literal);

    vector<vector<string>> IsApplicable(LiteralList *state, Action *action);

private:
    // Utilities

    static LiteralList *UnrollLiteralList(const LiteralList *rolled_list, const StringList *rolled_params,
                                          ParameterList *unrolled_params);

    static vector<Action *> *UnrollActions(vector<pair<Action *, vector<vector<string>>>> *rolled_actions);
};


#endif //PDDL_SOLVER_UTILS_H
