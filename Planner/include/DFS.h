#include "state_wrapper.h"
#include <unordered_map>
#include <queue>
#include "comparator.h"

using namespace std;

template<typename X>
X *DFS(X *initial, X *goal, long long &examined, long long &mem) {
    stack < X * > frontier;
    unordered_map<X, bool> closed;
    frontier.push(initial);
    examined = 0;
    mem = 1;
    while (frontier.size() > 0) {
        if ((long long) (frontier.size() + closed.size()) > mem)
            mem = frontier.size() + closed.size();
        examined++;
        X *s = frontier.top();
        frontier.pop();
        if (*s >= *goal) {
            cout << "Closed size: " << closed.size() << endl;
            return s;
        }
        closed[*s] = true;
        vector < X * > children = s->expand();
        for (unsigned int i = 0; i < children.size(); i++)
            if (!closed[*children.at(i)]) {
                frontier.push(children.at(i));
            }
    }
    return nullptr;
}
