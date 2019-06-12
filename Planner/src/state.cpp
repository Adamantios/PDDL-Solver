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
     string s="";
     State *p = this;
     while (p!=nullptr)
     {
          s = p->name+", "+s;
          p=p->father;
     }
     return s;
}
