#include "heuristics.h"
#include "pddldriver.hh"
#include "plan_utils.h"
#include "state.h"
#include "state_wrapper.h"
#include <cmath>
#include <md5.h>

StateWrapper::StateWrapper(LiteralList* literalList, Utils* utils,
    Heuristics* heuristics, StateWrapper* father)
{

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

StateWrapper::StateWrapper(StateWrapper* father, LiteralList* newLiteralList, Action* action)
{

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

Action*
StateWrapper::getLastAction()
{
    return _lastAction;
}

bool StateWrapper::isDebug()
{
    return _debug;
}

void StateWrapper::setDebug(bool debug)
{
    this->_debug = debug;
}

Utils*
StateWrapper::getUtils()
{
    return utils_;
}

Heuristics*
StateWrapper::getHeuristics()
{
    return _heuristics;
}

LiteralList*
StateWrapper::getLiteralList()
{
    return _literalList;
}

std::string StateWrapper::getId()
{
    if (this->_id == nullptr) {
        _id = new std::string();
        *_id += this->getName();
        for (unsigned int i = 0; i < this->_literalList->size(); i++) {
            *_id += _literalList->at(i)->first->getName();
        }
        *_id = md5(*_id);
    }
    return *_id;
}

std::string StateWrapper::getName()
{
    if (_name == nullptr) {
        _name = new std::string();
        std::vector<std::string> idsList;
        for (auto& literal : *_literalList)
            if (literal->second) {
                auto id = literal->first->getId();
                idsList.push_back(id);
            }
        sort(idsList.begin(), idsList.end());
        for (auto& predId : idsList)
            (*_name) += predId;
    }
    return *_name;
}

unsigned long long
StateWrapper::getHash() const
{
    if (this->_hash == 0) {
        int prefix = 0;
        for (unsigned i = 0; i < 5; i++) {
            prefix += pow(10, i) * ((int)_id->at(i));
        }
        int suffix = 0;
        for (unsigned i = 0; i < 3; i++) {
            suffix += pow(10, i) * ((int)_id->at(_id->length() - i - 1));
        }
        return static_cast<unsigned long long int>(prefix - suffix);
    }
    return this->_hash;
}

int StateWrapper::estimate()
{
    return static_cast<int>(_heuristics->Estimate(this->_literalList));
}

std::vector<StateWrapper*>
StateWrapper::expand()
{
    std::vector<Action*>* availableMoves = this->utils_->ApplicableActions(this->_literalList);
    std::vector<StateWrapper*> children;
    for (Action* availableMove : *availableMoves) {
        auto* child = new StateWrapper(this, Utils::NextState(this->_literalList, availableMove), availableMove);
        children.push_back(child);
        this->printExpandDebug(availableMove, child, static_cast<int>(children.size()));
    }
    return children;
}

void StateWrapper::printExpandDebug(Action* action, StateWrapper* child, int childrenNum)
{
    if (isDebug()) {
        std::cout << "++++++++++++++++++++ Expand Debug  ++++++++++++++++++++ " << std::endl;
        std::cout << "++++++++++++++++++++ Current State  ++++++++++++++++++++ " << std::endl;
        std::cout << *this << std::endl;
        std::cout << "++++++++++++++++++++     Action     +++++++++++++++++++ " << std::endl;
        std::cout << *action << std::endl;
        std::cout << "++++++++++++++++++++   Next State   ++++++++++++++++++++ " << std::endl;
        std::cout << *child << std::endl;
        std::cout << "+++++++++++++  Current Children Num = " << childrenNum << " ++++++++++++++" << std::endl;
        // cin.ignore();
    }
}

void StateWrapper::printActionsSequence()
{
    std::vector<Action*>* actions = this->getActions(this, new std::vector<Action*>);
    this->printActionsSequence(actions);
}

void StateWrapper::printActionsSequence(std::vector<Action*>* actions)
{
    for (Action* action : *actions) {
        std::cout << action->getName() << "(";
        const StringList* params = action->getParams();
        for (auto param = params->begin(); param != params->end(); ++param)
            if (param != params->begin())
                std::cout << "," << *param;
            else
                std::cout << *param;
        std::cout << ")" << std::endl;
    }
}

std::vector<Action*>*
StateWrapper::getActions(StateWrapper* state, std::vector<Action*>* actions)
{
    if (state->GetFather() == nullptr)
        return actions;
    else {
        actions = getActions((StateWrapper*)state->GetFather(), actions);
        actions->push_back(state->_lastAction);
    }
    return actions;
}

bool operator==(const StateWrapper& first, const StateWrapper& second)
{
    return *(first._id) == *(second._id);
}

bool operator<=(const StateWrapper& first, const StateWrapper& second)
{
    return second._name->find(*first._name) != std::string::npos;
}

bool operator>=(const StateWrapper& first, const StateWrapper& second)
{
    return first._name->find(*second._name) != std::string::npos;
}

std::ostream&
operator<<(std::ostream& out, const StateWrapper& state)
{
    out << "State{ " << std::endl;
    out << "\tPredicate List{" << std::endl;

    for (auto& literal : *state._literalList)
        if (literal->second)
            out << "\t\t" << *(literal->first) << std::endl;

    out << "\t}" << std::endl;
    out << "\t}" << std::endl;
    out << "\tHeuristic: " << state.hvalue_ << std::endl;
    out << "\tName: " << *(state._name) << std::endl;
    out << "\tID: " << *(state._id) << std::endl;
    out << "\tHash: " << state._hash << std::endl;
    out << "\tDepth: " << state.depth_ << std::endl;
    out << "\tChildren num: " << state.children_.size() << std::endl;
    std::cout << "}" << std::endl;

    return out;
}
