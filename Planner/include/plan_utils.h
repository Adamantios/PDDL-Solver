#ifndef PDDL_SOLVER_UTILS_H
#define PDDL_SOLVER_UTILS_H

#include "domain.hh"
#include "pddldriver.hh"
#include "predicate.hh"
#include <iostream>

class Utils {
protected:
    // VARIABLES
    PDDLDriver* driver_ {};

public:
    // CONSTRUCTORS
    Utils();

    explicit Utils(PDDLDriver* driver);

    virtual ~Utils();

    // FUNCTIONS
    // Gets

    std::vector<Action*> GetActions();

    LiteralList* GetGoal();

    // Utilities

    std::vector<Action*>* ApplicableActions(LiteralList* current_state);

    static LiteralList* NextState(LiteralList* state, Action* action);

    static bool LiteralsEqual(Literal* literal_1, Literal* literal_2);

    static LiteralList::iterator FindLiteral(LiteralList* state, Literal* literal);

    std::vector<std::vector<std::string>> IsApplicable(LiteralList* state, Action* action);

private:
    // Utilities

    static LiteralList* UnrollLiteralList(const LiteralList* rolled_list, const StringList* rolled_params,
        ParameterList* unrolled_params);

    static std::vector<Action*>* UnrollActions(std::vector<std::pair<Action*, std::vector<std::vector<std::string>>>>* rolled_actions);
};

#endif // PDDL_SOLVER_UTILS_H
