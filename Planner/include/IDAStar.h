#include "comparator.h"
#include "state_wrapper.h"
#include <queue>
#include <unordered_map>

template <typename X>
X* IDAstar(X* initial, X* goal, long long& examined, long long& mem)
{
    std::cout << "IDAstar is running...." << std::endl;
    double current_cost;
    double cost = 0;

    initial->SetHvalue(initial->estimate());

    while (true) {

        std::queue<X*> agenda = std::queue<X*>();
        std::unordered_map<X, bool> closed = std::unordered_map<X, bool>();

        agenda.push(initial);
        examined = 0;
        mem = 1;
        //       std::cout << "Examined: " << examined <<std::endl;
        //       std::cout << "Mem: " << mem <<std::endl;

        bool continue_search = true;
        while (continue_search && agenda.size() > 0) {
            //           std::cout << "Examined: " << examined <<std::endl;
            //           std::cout << "Mem: " << mem <<std::endl;
            if ((long long)(agenda.size() + closed.size()) > mem)
                mem = agenda.size() + closed.size();
            examined++;

            X* s = agenda.front();
            agenda.pop();

            current_cost = s->GetHvalue();

            if (*s >= *goal) {
                std::cout << "Closed size: " << closed.size() << std::endl;
                return s;
            }
            closed[*s] = true;

            if (current_cost > cost) { // Check if h value is larger than the current cost
                cost = current_cost;
                continue_search = false;
            } else { // Else add the expanded states in the agenda queue
                std::vector<X*> children = s->expand();
                for (unsigned int i = 0; i < children.size(); i++)
                    if (!closed[*children.at(i)]) {
                        children.at(i)->SetHvalue(children.at(i)->estimate());
                        agenda.push(children.at(i));
                    }
            }
        }
        std::cout << "Examined: " << examined << std::endl;
        std::cout << "Mem: " << mem << std::endl;

        // Examined all possible states and none matched the goal
        if (continue_search && agenda.size() <= 0)
            return nullptr;
    }
}
