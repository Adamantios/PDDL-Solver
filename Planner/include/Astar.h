#ifndef astar_def
#define astar_def
#include "algorithms.h"

template <typename X>
class Astar : public Algorithm{
public:
     X *run(X *initial,X *goal, long long &examined, long long &mem){
          priority_queue <X*, vector<X *>, Comparator<X> > agenda;
          unordered_map <X, bool> closed;
          agenda.push(initial);
          examined =0;
          mem=1;
          while (agenda.size()>0)
          {
               if (agenda.size() + closed.size() > mem)
                    mem = agenda.size() + closed.size();
               examined++;
               X *s = agenda.top();
               agenda.pop();
               if (*s==*goal)
                    return s;
               closed[*s]=true;
               vector<X *> children = s->expand();
               for (unsigned int i=0;i<children.size();i++)
                    if (!closed[*children.at(i)])
                    {
                         children.at(i)->setHvalue(children.at(i)->getDepth()+children.at(i)->heuristic(goal));
                         agenda.push(children.at(i));
                    }
          }
          return nullptr;
     }
}
#endif
