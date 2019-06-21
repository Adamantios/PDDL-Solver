#ifndef state_def
#define state_def

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>
#include <action.hh>

using namespace std;

class State{
 protected:
  State *father;
  vector<State *> children;
  int depth = 0;
  double Hvalue;
  string name;
  Action *action;

 public:
  // CON & DES
  State();
  ~State();

  // GETTERS
  int getDepth();
  double getHvalue();
  State *getFather();
  int getNoChildren();
  string getPath();
  Action* getAction();
  vector<State *> getChildren(){return children;};

  // SETTER
  void setFather(State* father);
  void setDepth(int d);
  void setHvalue(double h);

  //FUNCTIONS
  void addChild(State *);
  void removeChild(State *);
  virtual int heuristic (State *goal) {return 0;};

  // OVERWRITES
  bool operator>(State b){return getHvalue()>b.getHvalue();};
};

class myComparator
{
 public:
  int operator() (State *p1 , State *p2) const
  {
    return p1->getHvalue()>p2->getHvalue();
  }
};

#endif // state_def
