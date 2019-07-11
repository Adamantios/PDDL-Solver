#ifndef PDDL_SOLVER_STATE_H
#define PDDL_SOLVER_STATE_H

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>
#include <action.hh>

using namespace std;

class State {
protected:
    State *father_;
    vector<State *> children_;
    int depth_ = 0;
    double hvalue_{};

public:
    // CON & DES
    State();

    ~State();

    // GETTERS
    int GetDepth();

    double GetHvalue();

    State *GetFather();;

    // SETTER
    void SetFather(State *father);

    void SetDepth(int d);

    void SetHvalue(double h);

    void RemoveChild(State *child);

    // OVERWRITES
    bool operator>(State b) { return GetHvalue() > b.GetHvalue(); };
};

#endif //PDDL_SOLVER_STATE_H
