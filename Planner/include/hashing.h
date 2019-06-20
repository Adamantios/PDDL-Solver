#ifndef PDDL_SOLVER_HASHING_H
#define PDDL_SOLVER_HASHING_H

#include <map>
#include "pddldriver.hh"

using namespace std;


struct cmpByStringValue {
    bool operator()(const std::string* a, const std::string* b) const {
        return *a < *b;
    }
};

class Hashing {
protected:
    map<string*, unsigned int, cmpByStringValue>* nameDictionary;
    map<unsigned int, string*>* idDictionary;
    unsigned int next_id;
    string delimiter;

public:
    // CONSTRUCTORS
    Hashing();

    virtual ~Hashing();

    map<string*, unsigned int, cmpByStringValue>* GetNameDictionary();

    map<unsigned int, string*>* GetIDDictionary();

    void CreateDictionaries(PDDLDriver *driver);

    void AddToDictionary(string* name);

    vector<int> GetHashID(vector<string> objects);

    vector<string> GetObjectsFromHash(vector<int> hash);

    bool HasZero(unsigned int x);

    void PrintNameDictionary();

    void PrintIDDictionary();

    bool operator() (const string* s1, const string* s2) const;
};



#endif //PDDL_SOLVER_HASHING_H
