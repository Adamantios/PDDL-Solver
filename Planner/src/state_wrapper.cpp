#include "state.h"
#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"
#include "utils.h"
#include "heuristics.h"
#include "state_wrapper.h"
#include "md5.h"
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

using namespace std;

StateWrapper::StateWrapper(LiteralList *literalList, Utils *utils,
                           Heuristics *heuristics, StateWrapper *father) {

    this->_literalList = literalList;
    this->_heuristics = heuristics;
    this->utils_ = utils;
    this->SetFather(father);
    this->SetDepth(father != nullptr ? father->GetDepth() + 1 : 0);
    this->getName();
    this->getId();
    this->_hash = this->getHash();
    this->SetHvalue(_heuristics->Estimate(_literalList));
}

StateWrapper::StateWrapper(StateWrapper *father, LiteralList *newLiteralList, Action *action) {

    this->_literalList = newLiteralList;
    this->_heuristics = father->getHeuristics();
    this->utils_ = father->getUtils();
    this->SetFather(father);
    this->SetDepth(father->GetDepth() + 1);
    this->getId();
    this->_hash = this->getHash();
    this->SetHvalue(_heuristics->Estimate(newLiteralList));
    this->setDebug(father->isDebug());
    if (action != nullptr) {
        _lastAction = action;
    }
}

Action *
StateWrapper::getLastAction() {
    return _lastAction;
}


bool
StateWrapper::isDebug() {
    return _debug;
}

void
StateWrapper::setDebug(bool debug) {
    this->_debug = debug;
}


Utils *
StateWrapper::getUtils() {
    return utils_;
}

Heuristics *
StateWrapper::getHeuristics() {
    return _heuristics;
}

LiteralList *
StateWrapper::getLiteralList() {
    return _literalList;
}

string StateWrapper::getId() {
    if (this->_id == nullptr) {
        _id = new string();
        *_id += this->getName();
        for (unsigned int i = 0; i < this->_literalList->size(); i++) {
            *_id += _literalList->at(i)->first->getName();
        }
        *_id = md5(this->getName());
    }
    return *_id;
}

string StateWrapper::getName() {
    if (_name == nullptr) {
        _name = new string();
        vector<string> idsList;
        for (auto literal = _literalList->begin(); literal != _literalList->end(); ++literal) {
            if ((*literal)->second) {
                auto id = (*literal)->first->getId();
                idsList.push_back(id);
            }
        }
        sort(idsList.begin(), idsList.end());
        for (auto predId = idsList.begin(); predId != idsList.end(); ++predId) {
            (*_name) += (*predId);
        }
    }
    return *_name;
}

unsigned long long
StateWrapper::getHash() const {
    if (this->_hash == 0) {
        int prefix = 0;
        for (unsigned i = 0; i < 5; i++) {
            prefix += pow(10, i) * ((int) _id->at(i));
        }
        int sufix = 0;
        for (unsigned i = 0; i < 3; i++) {
            sufix += pow(10, i) * ((int) _id->at(_id->length() - i - 1));
        }
        return prefix - sufix;
    }
    return this->_hash;
}

int StateWrapper::estimate() {
    return _heuristics->Estimate(this->_literalList);
}

vector<StateWrapper *>
StateWrapper::expand() {
    vector<Action *> *availableMoves = this->utils_->ApplicableActions(this->_literalList);
    vector<StateWrapper *> children;
    for (Action *availableMove : *availableMoves) {
        StateWrapper *child = new StateWrapper(this,
                                               this->utils_->NextState(this->_literalList, availableMove),
                                               availableMove);
        children.push_back(child);
        this->printExpandDebug(availableMove, child, children.size());
    }
    return children;
}

void
StateWrapper::printExpandDebug(Action *action, StateWrapper *child, int childrenNum) {
    if (isDebug()) {
        cout << "++++++++++++++++++++ Expand Debug  ++++++++++++++++++++ " << endl;
        cout << "++++++++++++++++++++ Current State  ++++++++++++++++++++ " << endl;
        cout << *this << endl;
        cout << "++++++++++++++++++++     Action     +++++++++++++++++++ " << endl;
        cout << *action << endl;
        cout << "++++++++++++++++++++   Next State   ++++++++++++++++++++ " << endl;
        cout << *child << endl;
        cout << "+++++++++++++  Current Children Num = " << childrenNum << " ++++++++++++++" << endl;
        //cin.ignore();
    }
}

void
StateWrapper::printActionsSequence() {
    vector<Action *> *actions = this->getActions(this, new vector<Action *>);
    this->printActionsSequence(actions);
}

void
StateWrapper::printActionsSequence(vector<Action *> *actions) {
    for (Action *action : *actions) {
        cout << action->getName() << "(";
        const StringList *params = action->getParams();
        for (vector<string>::const_iterator param = params->begin();
             param != params->end(); ++param) {

            if (param != params->begin()) {
                cout << "," << *param;
            } else {
                cout << *param;
            }

        }
        cout << ")" << endl;
    }
}

vector<Action *> *
StateWrapper::getActions(StateWrapper *state, vector<Action *> *actions) {
    if (state->GetFather() == nullptr) {
        return actions;
    } else {
        actions = getActions((StateWrapper *) state->GetFather(), actions);
        actions->push_back(state->_lastAction);
    }
    return actions;
}

bool
operator==(const StateWrapper first, const StateWrapper second) {
    return *(first._id) == *(second._id);
}

bool
operator<=(const StateWrapper first, const StateWrapper second) {
    if (second._name->find(*first._name) != std::string::npos) {
        return true;
    }
    return false;
}

bool
operator>=(const StateWrapper first, const StateWrapper second) {
    if (first._name->find(*second._name) != std::string::npos) {
        return true;
    }
    return false;
}

ostream &
operator<<(std::ostream &out, const StateWrapper &state) {
    out << "State{ " << endl;
    out << "\tPredicate List{" << endl;
    for (auto literal = state._literalList->begin(); literal != state._literalList->end(); ++literal) {
        if ((*literal)->second) {
            out << "\t\t" << *((*literal)->first) << endl;
        }
    }
    out << "\t}" << endl;
    // out << "\tAction List{" << endl;
    // for(Action *action : state.getActions(state, new vector<Action *>)){
    //      out << "\t\t" << *action <<endl;
    // }
    out << "\t}" << endl;
    out << "\tHeuristic: " << state.hvalue_ << endl;
    out << "\tName: " << *(state._name) << endl;
    out << "\tID: " << *(state._id) << endl;
    out << "\tHash: " << state._hash << endl;
    out << "\tDepth: " << state.depth_ << endl;
    out << "\tChildren num: " << state.children_.size() << endl;
    cout << "}" << endl;
}


