#include "state_wrapper.h"
#include <unordered_map>
#include <queue>
#include "comparator.h"

using namespace std;

template<typename X>
X *IDAstar(X *initial, X *goal, long long &examined, long long &mem) {
    cout << "IDAstar is running...." << endl;
    double current_cost;
    double cost = 0;

    initial->SetHvalue(initial->estimate());

    while (true) {

        queue<X *> agenda = queue<X *>();
        unordered_map<X, bool> closed = unordered_map<X, bool>();

        agenda.push(initial);
        examined = 0;
        mem = 1;
//        cout << "Examined: " << examined << endl;
//        cout << "Mem: " << mem << endl;

        bool continue_search = true;
        while (continue_search && agenda.size() > 0) {
//            cout << "Examined: " << examined << endl;
//            cout << "Mem: " << mem << endl;
            if ((long long) (agenda.size() + closed.size()) > mem)
                mem = agenda.size() + closed.size();
            examined++;

            X *s = agenda.front();
            agenda.pop();

            current_cost = s->GetHvalue();

            if (*s >= *goal) {
                cout << "Closed size: " << closed.size() << endl;
                return s;
            }
            closed[*s] = true;


            if (current_cost > cost) { // Check if h value is larger than the current cost
                cost = current_cost;
                continue_search = false;
            } else { // Else add the expanded states in the agenda queue
                vector<X *> children = s->expand();
                for (unsigned int i = 0; i < children.size(); i++)
                    if (!closed[*children.at(i)]) {
                        children.at(i)->SetHvalue(children.at(i)->estimate());
                        agenda.push(children.at(i));
                    }
            }
        }
        cout << "Examined: " << examined << endl;
        cout << "Mem: " << mem << endl;

        // Examined all possible states and none matched the goal
        if (continue_search && agenda.size() <= 0) return nullptr;
    }
}
