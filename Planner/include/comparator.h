#ifndef PDDL_SOLVER_COMPARATOR_H
#define PDDL_SOLVER_COMPARATOR_H

#include "state_wrapper.h"
#include <unordered_map>
#include <queue>

using namespace std;

template<typename X>
class Comparator {
public:
    int operator()(X *p_1, X *p_2) const {
        return *p_1 > *p_2;
    }
};

#endif //PDDL_SOLVER_COMPARATOR_H
