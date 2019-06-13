#include "state.h"

#ifndef search_def
#define search_def

using namespace std;

template <typename X>
class Comparator
{
public:
     int operator() (X *p1 , X *p2) const
     {
          return *p1>*p2;
     }
};

template <typename X>
X *Astar(X *initial,X *goal, long long &examined, long long &mem){
     priority_queue <X*, vector<X *>, Comparator<X> > agenda;
     unordered_map <X, bool> closed;
     agenda.push(initial);
     examined =0;
     mem=1;
     while (agenda.size()>0) {
          if (agenda.size() + closed.size() > mem)
               mem = agenda.size() + closed.size();
          examined++;
          X *s = agenda.top();
          /* cout << *s <<endl; */
          /* cin.ignore(); */
          agenda.pop();
          if (*s >= *goal)
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
#endif
