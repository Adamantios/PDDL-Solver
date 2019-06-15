
#include <hashing.h>

#include "hashing.h"

Hashing::Hashing() {
    // Start id variable from 1
    next_id = 1;
    delimiter = "0";
}

Hashing::~Hashing() {
   if (nameDictionary) delete (nameDictionary);
   if (idDictionary) delete (idDictionary);
}

map<string*, unsigned int, cmpByStringValue> *Hashing::GetNameDictionary() {
    return nameDictionary;
}


map<unsigned int, string*> *Hashing::GetIDDictionary() {
    return idDictionary;
}

void Hashing::PrintNameDictionary() {
    for ( map<string*, unsigned int, cmpByStringValue>::iterator it = nameDictionary->begin(); it != nameDictionary->end(); it++ )
    {
        std::cout <<*(it->first) // string (key)
                  << " : "
                  << it->second   // int's value
                  << std::endl ;
    }
}

void Hashing::PrintIDDictionary() {
    for ( map<unsigned int, string*>::iterator it = idDictionary->begin(); it != idDictionary->end(); it++ )
    {
        std::cout << it->first  // int (key)
                  << " : "
                  << *(it->second)  // string's value
                  << std::endl ;
    }
}

/**
 *
 * @param x 0 or positive integer
 * @return true if x contains at least on digit that is a 0
 */
bool Hashing::HasZero(unsigned int x) {
    if (x == 0) return true;
    if (x < 10) return false;
    return HasZero(x % 10);
}

/**
 * Add the provided string in the dictionaries
 * Increment next_id to the next valid integer
 * @param name the string to add to the dictionaries
 */
void Hashing::AddToDictionary(string* name) {
    // Add to dictionary
    nameDictionary->insert(pair<string*, unsigned int>(name, next_id));
    idDictionary->insert(pair<unsigned int, string*>(next_id, name));

    // Assign next id
    do{
        next_id++;
    } while(HasZero(next_id));
}

/**
 * Initialize name and id dictionaries
 * Fill dictionaries with the action names, the state objects and the
 * init and goal state variables
 * @param driver PDDLDriver
 */
void Hashing::CreateDictionaries(PDDLDriver *driver) {
    nameDictionary = new map<string*, unsigned int, cmpByStringValue>();
    idDictionary = new map<unsigned int, string*>();

    // Action pointer
    Action *action;
    // String variable
    string* object;

    // Actions loop
    for (unsigned int i = 0; i < driver->domain->getActions()->size(); i++) {
        // Assign current action
        action = driver->domain->getActions()->at(i);
        object = new string(action->getName());
        // Add action to dictionary
        AddToDictionary(object);
    }

    // Problem objects loop
    for (unsigned int i = 0; i < driver->problem->getObjects()->size(); i++) {
        // Add current object to dictionary
        object = new string(driver->problem->getObjects()->at(i));
        AddToDictionary(object);
    }

    // Problem init state loop
    for (unsigned int i = 0; i < driver->problem->getInit()->size(); i++) {
        // Add current object to dictionary
        object = new string(driver->problem->getInit()->at(i)->first->getName());
        AddToDictionary(object);
    }

    // Problem goal state loop
    for (unsigned int i = 0; i < driver->problem->getGoal()->size(); i++) {
        // Add current object to dictionary
        object = new string(driver->problem->getGoal()->at(i)->first->getName());
        AddToDictionary(object);
    }
}

/**
 * Create and return the hash for these objects
 * @param objects vector with name and params of the state/action
 * @return integer hash
 */
unsigned int Hashing::GetHashID(vector<string> objects) {
    string id = "";
    for (unsigned int i = 0; i < objects.size(); i++) {
        id += to_string((*nameDictionary)[&(objects.at(i))]) + "" + delimiter;
    }
    cout<<id<<endl;
    return stoi(id);
}

/**
 *
 * @param hash of action/state
 * @return vector of strings with the name and params according to the hash order
 */
vector<string> Hashing::GetObjectsFromHash(unsigned int hash) {
    vector<string> objects = vector<string>();
    string id = to_string(hash);

    // Split hash
    size_t pos = 0;
    string token;
    unsigned int single_id;
    while ((pos = id.find(delimiter)) != std::string::npos) {
        // Get single id
        token = id.substr(0, pos);
        // Remove from string
        id.erase(0, pos + delimiter.length());

        single_id = stoi(token);
        // Check if id exists in id dictionary
        if (idDictionary->count(single_id)) {
            objects.push_back(*(*idDictionary)[single_id]);
            cout<<*(*idDictionary)[single_id]<<endl;
        }
    }

    return objects;
}

bool Hashing::operator() (const string* s1, const string* s2) const
{
    return *s1 < *s2;
}




