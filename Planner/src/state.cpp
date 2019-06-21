#include "state.h"
#include <iostream>
#include <algorithm>

State::State()
{
     father=nullptr;
}
State::~State()
{
     if (father!=nullptr)
          father->removeChild(this);
}
int State::getDepth()
{
     return depth;
}
void State::setDepth(int d)
{
     depth=d;
}

void State::setFather(State* father){
     this->father = father;
}

void State::setHvalue(double h)
{
     Hvalue = h;
}
double State::getHvalue()
{
     return Hvalue;
}
State *State::getFather()
{
     return father;
}
void State::addChild(State *c)
{
     children.push_back(c);
}
void State::removeChild(State *c)
{
     children.erase(std::remove(children.begin(), children.end(), c), children.end());
}

int State::getNoChildren()
{
     return children.size();
}
string State::getPath()
{
     string s = "";
     string a = "";
     State *p = this;
     while (p->father != nullptr)
     {
          a = p->action->getName() + " : ";
          for(unsigned int i=0; i<p->action->getParams()->size(); i++){
              a += p->action->getParams()->at(i) + " ";
          }
          a += " , ";
          s = a + s;
          p = p->father;
     }
     return s;
}


Action*
State::getAction(){
    return action;
}
