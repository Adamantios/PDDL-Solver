#include "problem.hh"

;

Problem::Problem(const std::string& name, const std::string& domain)
    : _name(name)
    , _domain(domain)
{
}

Problem::~Problem()
{
    delete _objects;

    for (auto literal : *_init) {
        delete literal->first;
    }
    delete _init;

    for (auto goal : *_goal) {
        delete goal->first;
    }
    delete _goal;
}

void Problem::set_objects(StringList* objects)
{
    _objects = objects;
}

void Problem::set_init_state(LiteralList* init)
{
    _init = init;
}

LiteralList*
Problem::getInit()
{
    return _init;
}

LiteralList*
Problem::getGoal()
{
    return _goal;
}

void Problem::set_goal_state(LiteralList* goal)
{
    _goal = goal;
}

StringList*
Problem::getObjects()
{
    return _objects;
}

std::ostream&
operator<<(std::ostream& out, const Problem& problem)
{
    out << ">> Problem(name:" << problem._name << ", domain:" << problem._domain << ")" << std::endl;
    out << std::endl;
    out << "Objects: [";
    for (auto const& object : *problem._objects) {
        out << " " << object;
    }
    out << " ]" << std::endl;
    out << std::endl;
    out << "Init: [" << std::endl;
    for (auto const& literal : *problem._init) {
        if (literal->second) {
            out << "  " << *(literal->first);
        } else {
            out << "  NOT " << *(literal->first);
        }
        out << std::endl;
    }
    out << "]" << std::endl;
    out << std::endl;
    out << "Goal: [" << std::endl;
    for (auto const& literal : *problem._goal) {
        if (literal->second) {
            out << "  " << *(literal->first);
        } else {
            out << "  NOT " << *(literal->first);
        }
        out << std::endl;
    }
    out << "]" << std::endl;

    return out;
}
