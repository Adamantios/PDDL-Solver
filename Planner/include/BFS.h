#include "state_wrapper.h"
#include <unordered_map>
#include <queue>
#include "comparator.h"

using namespace std;

template<typename X>
X *BFS(X *initial, X *goal, long long &examined, long long &mem) {
  priority_queue<X *, vector<X *>, Comparator<X> > agenda;
  unordered_map<string, bool> closed;
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
      cout << "Closed size: " << closed.size() << endl;
      return s;
    }
    closed[s->getId()] = true;
    vector<X *> children = s->expand();
    for (unsigned int i = 0; i < children.size(); i++)
      if (!closed[children.at(i)->getId()]) {
        children.at(i)->SetHvalue(children.at(i)->estimate());
        agenda.push(children.at(i));
      }
  }
  return nullptr;
}
