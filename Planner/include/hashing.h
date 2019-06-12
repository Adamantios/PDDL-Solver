#ifndef PDDL_SOLVER_HASHING_H
#define PDDL_SOLVER_HASHING_H

#include <map>
#include "pddldriver.hh"

using namespace std;

class Hashing {
protected:
    map<string, int>* nameDictionary;
    map<int, string>* idDictionary;
    int next_id;
    string delimiter;

public:
    // CONSTRUCTORS
    Hashing();

    virtual ~Hashing();

    map<string, int>* GetNameDictionary();

    map<int, string>* GetIDDictionary();

    void CreateDictionaries(PDDLDriver *driver);

    void AddToDictionary(string name);

    unsigned int GetHashID(vector<string> objects);

    vector<string> GetObjectsFromHash(unsigned int hash);

    bool HasZero(int x);

    void PrintNameDictionary();

    void PrintIDDictionary();
};


#endif //PDDL_SOLVER_HASHING_H
