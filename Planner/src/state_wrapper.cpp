#include "state.h"
#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"
#include "ParserController.h"
#include "heuristics.h"
#include "state_wrapper.h"
#include "md5.h"

#include <algorithm>
#include <string>
#include <math.h>
using namespace std;

StateWrapper::StateWrapper(LiteralList* literalList, ParserController* parserController,
                           Heuristics* heuristics, StateWrapper* father){

     this->_literalList = literalList;
     this->_heuristics = heuristics;
     this->_parserController = parserController;
     this->setFather(father);
     this->setDepth(father != nullptr ? father->getDepth() + 1: 0);
     this->getName();
     this->getId();
     this->_hash = this->getHash();
     this->setHvalue(_heuristics->Estimate(_literalList));
}

StateWrapper::StateWrapper(StateWrapper* father, LiteralList* newLiteralList, Action* action){

     this->_literalList = newLiteralList;
     this->_heuristics = father->getHeuristics();
     this->_parserController = father->getParserController();
     this->setFather(father);
     this->setDepth(father != nullptr ? father->getDepth() + 1: 0);
     this->getId();
     this->_hash = this->getHash();
     this->setHvalue(_heuristics->Estimate(newLiteralList));
     this->setDebug(father->isDebug());

     // if(father != nullptr && action != nullptr){
     //      vector<Action> vect(*(father->getActions()));
     //      vect.push_back(*action);
     //      cout << "Add action: " << *action << endl;
     // }else{
     //      vector<Action> vect;
     //      _actions = &vect;
     // }

}

// vector<Action>*
// StateWrapper::getActions(){
//      return _actions;
// }

bool
StateWrapper::isDebug(){
     return _debug;
}

void
StateWrapper::setDebug(bool debug){
     this->_debug = debug;
}


ParserController*
StateWrapper::getParserController(){
     return _parserController;
}

Heuristics*
StateWrapper::getHeuristics(){
     return _heuristics;
}

LiteralList*
StateWrapper::getLiteralList(){
     return _literalList;
}

string StateWrapper::getId(){
     if(this->_id == nullptr){
          _id = new string();
          *_id = md5(this->getName());
     }
     return *_id;
}
 
string StateWrapper::getName(){
     if(_name == nullptr){
          _name = new string();
          vector<string> idsList;
          for(auto literal = _literalList->begin(); literal != _literalList->end(); ++literal){
               if( (*literal)->second){
                    auto id = (*literal)->first->getId();
                    idsList.push_back(id);
               }
          }
          sort(idsList.begin(),idsList.end());
          for(auto predId = idsList.begin(); predId != idsList.end(); ++predId){
               (*_name) += (*predId);
          }
     }
     return *_name;
}

unsigned long long
StateWrapper::getHash() const{
     if(this->_hash == 0){
          int prefix = 0;
          for(unsigned i = 0; i < 5; i++){
               prefix += pow(10,i) * ((int) _id->at(i));
          }
          int sufix = 0;
          for(unsigned i = 0; i < 3; i++){
               sufix += pow(10,i) * ((int) _id->at(_id->length() - i - 1));
          }
          return prefix - sufix;
     }
     return this->_hash;
}

vector<StateWrapper*>
StateWrapper::expand(){
     vector<Action*>* availableMoves = this->_parserController->ApplicableActions(this->_literalList);
     vector<StateWrapper*> children;
     for(auto action = availableMoves->begin(); action != availableMoves->end(); ++action){
          // cout << "++++++++++++++++++++     Action     +++++++++++++++++++ " << endl;
          // cout << **action << endl;
          StateWrapper* child = new StateWrapper(this,
                                                 this->_parserController->NextState(this->_literalList, **action),
                                                 *action);
          this->addChild(child);
          children.push_back(child);
          this->printExpandDebug(*action, child, children.size());
     }
     return children;
}

void
StateWrapper::printExpandDebug(Action* action, StateWrapper* child, int childrenNum){
     if(isDebug()){
          cout << "++++++++++++++++++++ Expand Debug  ++++++++++++++++++++ " << endl;
          cout << "++++++++++++++++++++ Current State  ++++++++++++++++++++ " << endl;
          cout << *this << endl;
          // cout << "++++++++++++++++++++     Action     +++++++++++++++++++ " << endl;
          // cout << *action << endl;
          cout << "++++++++++++++++++++   Next State   ++++++++++++++++++++ " << endl;
          cout << *child << endl;
          cout << "+++++++++++++  Current Children Num = " << childrenNum << " ++++++++++++++" << endl;
          cin.ignore();
     }
}

bool
operator==(const StateWrapper first, const StateWrapper second){
     return *(first._id) == *(second._id);
}

bool
operator<=(const StateWrapper first, const StateWrapper second){
     if(second._name->find(*first._name) != std::string::npos){
          return true;
     }
     return false;
}

bool
operator>=(const StateWrapper first, const StateWrapper second){
     if(first._name->find(*second._name) != std::string::npos){
          return true;
     }
     return false;
}

ostream &
operator<<(std::ostream &out, const StateWrapper &state){
     out << "State{ " << endl;
     out << "\tPredicate List{" << endl;
     for(auto literal = state._literalList->begin(); literal != state._literalList->end(); ++literal){
          if((*literal)->second){
               out << "\t\t" << *((*literal)->first) << endl;
          }
     }
     out << "\t}" << endl;
     out << "\tAction List{" << endl;
     // if(state._actions != nullptr and state._actions->size()){
     //   for(auto action = state._actions->begin(); action != state._actions->end(); ++action){
     //     out << "\t\t" << *action <<endl;
     //   }
     // }
     out << "\t}" << endl;
     out << "\tHeuristic: " << state.Hvalue << endl;
     out << "\tName: " << *(state._name) << endl;
     out << "\tID: " << *(state._id) << endl;
     out << "\tHash: " << state._hash << endl;
     out << "\tDepth: " << state.depth << endl;
     out << "\tChildren num: " << state.children.size() << endl;
     cout << "}" << endl;
}
