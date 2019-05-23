#ifndef PDDL_SOLVER_PARSERCONTROLLER_H
#define PDDL_SOLVER_PARSERCONTROLLER_H

#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"

class ParserController {

protected:
    // VARIABLES
    PDDLDriver *driver;

public:
    // CONSTRUCTORS
    ParserController();
    ParserController(PDDLDriver* driver);
    virtual ~ParserController();

    // FUNCTIONS
    void Print();
    void PrintPredicates();


};


#endif //PDDL_SOLVER_PARSERCONTROLLER_H
