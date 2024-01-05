#include "predicate.hh"
#include <algorithm>

;

Predicate::Predicate(std::string name, ArgumentList* args)
    : _name(name)
    , _args(args->first)
    , _types(args->second)
{
    this->_id = this->computeId();
}

const std::string Predicate::computeId() const
{
    std::string id = this->_name + "_";
    sort(_args->begin(), _args->end());
    for (auto arg = _args->begin(); arg != _args->end(); ++arg) {
        id += *arg;
    }
    return id;
}

const std::string Predicate::getId() const
{
    return _id;
}

const std::string& Predicate::getName() const
{
    return _name;
}

StringList* Predicate::getArgs() const
{
    return _args;
}

TypeDict* Predicate::getTypes() const
{
    return _types;
}

Predicate::~Predicate()
{
    if (_args)
        delete _args;
    if (_types)
        delete _types;
}

std::ostream&
operator<<(std::ostream& out, const Predicate& predicate)
{
    out << predicate._name << "(";
    int i = 0;
    for (auto arg : *(predicate._args)) {
        if (i == 0) {
            out << arg;
        } else {
            out << "," << arg;
        }
        ++i;
    }
    out << ")";
    return out;
}
