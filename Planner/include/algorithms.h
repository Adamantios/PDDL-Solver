#include "state.h"
#include <unordered_map>
#include <queue>

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

template <typename X>
X *BFS(X *initial,X *goal, long long &examined, long long &mem){
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
        agenda.pop();
        if (*s >= *goal)
            return s;
        closed[*s]=true;
        vector<X *> children = s->expand();
        for (unsigned int i=0;i<children.size();i++)
            if (!closed[*children.at(i)])
            {
                children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                agenda.push(children.at(i));
            }
    }
    return nullptr;
}

template <typename X>
X *IDAstar(X *initial,X *goal, long long &examined, long long &mem){
    double current_cost;
    double cost = 0;

    initial->setHvalue(initial->heuristic(goal));

    while(true) {

        queue <X*> agenda = queue<X*>();
        unordered_map <X, bool> closed = unordered_map<X, bool>();

        agenda.push(initial);
        examined = 0;
        mem = 1;
        cout<<"Examined: "<<examined<<endl;
        cout<<"Mem: "<<mem<<endl;

        bool continue_search = true;
        while (continue_search && agenda.size() > 0) {
            cout<<"Examined: "<<examined<<endl;
            cout<<"Mem: "<<mem<<endl;
            if (agenda.size() + closed.size() > mem)
                mem = agenda.size() + closed.size();
            examined++;

            X* s = agenda.front();
            agenda.pop();

            current_cost = s->getHvalue();

            if (*s >= *goal) // Found goal
                return s;
            closed[*s] = true;


            if (current_cost > cost ) { // Check if h value is larger than the current cost
                cost = current_cost;
                continue_search = false;
            }
            else { // Else add the expanded states in the agenda queue
                vector<X *> children = s->expand();
                for (unsigned int i=0;i<children.size();i++)
                    if (!closed[*children.at(i)])
                    {
                        children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                        agenda.push(children.at(i));
                    }
            }
        }
        cout<<"Examined: "<<examined<<endl;
        cout<<"Mem: "<<mem<<endl;

        // Examined all possible states and none matched the goal
        if (continue_search && agenda.size() <= 0) return nullptr;

    }


    return nullptr;
}

template <typename X>
X *DFS(X *initial,X *goal, long long &examined, long long &mem){
    queue <X*> frontier;
    unordered_map <X, bool> closed;
    frontier.push(initial);
    examined =0;
    mem=1;
    while (frontier.size()>0) {
        if (frontier.size() + closed.size() > mem)
            mem = frontier.size() + closed.size();
        examined++;
        X *s = frontier.top();
        frontier.pop();
        if (*s >= *goal)
            return s;
        closed[*s]=true;
        vector<X *> children = s->expand();
        for (unsigned int i=0;i<children.size();i++)
            if (!closed[*children.at(i)])
            {
                frontier.push(children.at(i));
            }
    }
    return nullptr;
}
#endif
