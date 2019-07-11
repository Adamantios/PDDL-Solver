#ifndef __PREDICATE_HH__
#define __PREDICATE_HH__

#include <string>
#include <vector>
#include <map>
#include <iostream>

using StringList   = std::vector<std::string>;
using TypeDict     = std::map<std::string, std::string>;
using ArgumentList = std::pair<StringList *, TypeDict *>;

class Predicate {
public:
    Predicate(std::string name, ArgumentList *args);

    const std::string &getName() const;

    const std::string getId() const;

    StringList *getArgs() const;

    TypeDict *getTypes() const;

    virtual ~Predicate();

    friend std::ostream &operator<<(std::ostream &out, const Predicate &predicate);

private:
    const std::string computeId() const;

    std::string _name;
    StringList *_args;
    TypeDict *_types;
    std::string _id;
};

#endif
