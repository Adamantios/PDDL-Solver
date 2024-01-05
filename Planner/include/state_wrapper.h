#ifndef PDDL_SOLVER_STATE_WRAPPER_H
#define PDDL_SOLVER_STATE_WRAPPER_H

#include "domain.hh"
#include "heuristics.h"
#include "pddldriver.hh"
#include "plan_utils.h"
#include "predicate.hh"
#include "state.h"

class StateWrapper : public State {
private:
    LiteralList* _literalList;
    Utils* utils_;
    Heuristics* _heuristics;
    std::string* _id = nullptr;
    std::string* _name = nullptr;

    unsigned long long _hash = 0;
    bool _debug {};
    Action* _lastAction {};

public:
    // Constructors
    StateWrapper(LiteralList* literalList, Utils* utils, Heuristics* heuristics, StateWrapper* father);

    StateWrapper(StateWrapper* father, LiteralList* newLiteralList, Action* action);

    std::string getId();

    //@Override
    std::vector<StateWrapper*> expand();

    // Getters
    unsigned long long getHash() const;

    friend std::ostream& operator<<(std::ostream& out, const StateWrapper& state);

    friend bool operator==(const StateWrapper& first, const StateWrapper& second);

    friend bool operator<=(const StateWrapper& first, const StateWrapper& second);

    friend bool operator>=(const StateWrapper& first, const StateWrapper& second);

    bool isDebug();

    std::string getName();

    LiteralList* getLiteralList();

    Heuristics* getHeuristics();

    Utils* getUtils();

    Action* getLastAction();

    int estimate();

    // Setters
    void setDebug(bool debug);

    // Debugging Functionality
    void printExpandDebug(Action* action, StateWrapper* child, int childrenNum);

    static void printActionsSequence(std::vector<Action*>* actions);

    void printActionsSequence();

    static std::vector<Action*>* getActions(StateWrapper* state, std::vector<Action*>* actions);
};

namespace std {
template <>
class hash<StateWrapper> {
public:
    size_t operator()(const StateWrapper& a) const
    {
        return a.getHash();
    }
};
}
#endif // PDDL_SOLVER_STATE_WRAPPER_H
