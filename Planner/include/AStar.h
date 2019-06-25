#include "state_wrapper.h"
#include <unordered_map>
#include <queue>
#include "comparator.h"

using namespace std;

template<typename X>
X *Astar(X *initial, X *goal, long long &examined, long long &mem) {
    cout << "AStar is running...." << endl;
    priority_queue<X *, vector<X *>, Comparator<X> > agenda;
    unordered_map<unsigned long long, bool> closed;
    agenda.push(initial);
    examined = 0;
    mem = 1;
    while (agenda.size() > 0) {
        if ((long long) (agenda.size() + closed.size()) > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s >= *goal) {
            return s;
        }
        closed[s->getHash()] = true;
        vector<X *> children = s->expand();
        for (unsigned int i = 0; i < children.size(); i++)
            if (!closed[children.at(i)->getHash()]) {
                children.at(i)->SetHvalue(children.at(i)->GetDepth() + children.at(i)->estimate());
                agenda.push(children.at(i));
            }
    }
    return nullptr;
}
