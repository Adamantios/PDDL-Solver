#include "domain.hh"

;

Domain::Domain(const std::string& name)
    : _name(name)
{
}

const std::string& Domain::getName() const
{
    return _name;
}

std::vector<std::string>* Domain::getRequirements() const
{
    return _requirements;
}

std::vector<Predicate*>* Domain::getPredicates() const
{
    return _predicates;
}

std::vector<Action*>* Domain::getActions() const
{
    return _actions;
}

Domain::~Domain()
{
    for (auto predicate : *_predicates) {
        delete predicate;
        predicate = nullptr;
    }
    delete _predicates;

    for (auto action : *_actions) {
        delete action;
        action = nullptr;
    }
    delete _actions;
}

void Domain::set_requirements(std::vector<std::string>* requirements)
{
    _requirements = requirements;
}

void Domain::set_predicates(std::vector<Predicate*>* predicates)
{
    _predicates = predicates;
}

void Domain::set_actions(std::vector<Action*>* actions)
{
    _actions = actions;
}

std::ostream&
operator<<(std::ostream& out, const Domain& domain)
{
    out << ">> Domain(name:" << domain._name << ")" << std::endl;
    out << std::endl;
    out << "Requirements: [";
    for (auto const& requirement : *domain._requirements) {
        out << " " << requirement;
    }
    out << " ]" << std::endl;
    out << "Predicates: [";
    for (auto const& predicate : *domain._predicates) {
        out << " " << *predicate;
    }
    out << " ]" << std::endl;
    out << std::endl;
    for (auto const& action : *domain._actions) {
        out << *action;
        out << std::endl;
    }
    return out;
}
