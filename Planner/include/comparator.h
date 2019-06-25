#include "state_wrapper.h"
#include <unordered_map>
#include <queue>

#ifndef SEARCH_DEF
#define SEARCH_DEF

using namespace std;

template<typename X>
class Comparator {
public:
    int operator()(X *p_1, X *p_2) const {
        return *p_1 > *p_2;
    }
};
#endif
