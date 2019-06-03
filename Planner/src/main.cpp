// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "heuristics_demo.h"
#include "pddldriver.hh"
#include "ParserController.h"

using namespace std;

void usage(char *filename);

int main (int argc, char *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return -1;
    }

    int result = 0;

    auto *driver = new PDDLDriver();

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == string ("-p")) {
            driver->trace_parsing = true;
        }
        else if (argv[i] == string ("-s")) {
            driver->trace_scanning = true;
        }
        else if (!driver->parse(argv[i])) {
            cout << "Parsing " << argv[i] << "... ";
            if (!result) cout << "ok!" << endl;
            else cout << "Error!" << endl;
        }
        else {
            result = -2;
            break;
        }
    }

    // Init Controller.
    ParserController parserController;
    parserController = ParserController(driver);

    // Test with print function
    // parserController.Print();
    // parserController.PrintPredicates();

    /* Kostas Tsampazis
     * Demonstration of ParserController functionality of ApplicableActions utility method
     */
    LiteralList *currentState = driver->problem->getInit();
    // vector<Action*> applicableActions = parserController.ApplicableActions(currentState);
    // if (applicableActions.empty()) cout << "No applicable actions on this state";
    // else {
    //     cout << "Applicable action(s): " << endl;
    //     for (unsigned int i = 0; i < applicableActions.size(); i++)
    //         cout << applicableActions.at(i)->_name << ", ";
    // }
    // cout << endl;

    // Run heuristics demo.
    HeuristicsDemo(parserController, currentState);

    if (driver) delete(driver);

    return result;
}

void usage(char *filename)
{
    cout << "usage: " << filename << " [-s] [-p] <domain.pddl> <problem.pddl>" << endl;
    cout << endl;
    cout << "OPTIONS:" << endl;
    cout << " -s\tenable scanning trace." << endl;
    cout << " -p\tenable parsing trace."  << endl;
}
