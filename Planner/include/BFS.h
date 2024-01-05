#include "comparator.h"
#include "state_wrapper.h"
#include <queue>
#include <unordered_map>

template <typename X>
X* BFS(X* initial, X* goal, long long& examined, long long& mem)
{
    std::cout << "BFS is running...." << std::endl;
    std::unordered_map<std::string, bool> closed;
    std::priority_queue<X*, std::vector<X*>, Comparator<X>> agenda;
    agenda.push(initial);
    examined = 0;
    mem = 1;
    while (agenda.size() > 0) {
        if ((long long)(agenda.size() + closed.size()) > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X* s = agenda.top();
        agenda.pop();
        if (*s >= *goal) {
            std::cout << "Closed size: " << closed.size() << std::endl;
            return s;
        }
        closed[s->getId()] = true;
        std::vector<X*> children = s->expand();
        for (unsigned int i = 0; i < children.size(); i++)
            if (!closed[children.at(i)->getId()]) {
                children.at(i)->SetHvalue(children.at(i)->estimate());
                agenda.push(children.at(i));
            }
    }
    return nullptr;
}
