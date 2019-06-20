// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <heuristics_demo.h>
#include "pddldriver.hh"
#include "ParserController.h"
#include "hashing.h"
#include "CLI11.hpp"

using namespace std;

string APP_DESCRIPTION = "This application implements a pddl solver."; // Write More
string AVAILABLE_ALGORITHMS = "You can choose an algorithm among the following ones:\nA_STAR";
string AVAILABLE_HEURISTICS = "You can choose a heuristic among the following ones:\nMAX_COST";

void usage(char *filename);

std::shared_ptr<CLI::App> setUpCLI(string &domain_file, string &problem_file,
                                   bool &scanning_trace, bool &parsing_trace,
                                   string &algorithm, string &heuristic);

std::shared_ptr<CLI::App> get_app() {
    auto app = std::make_shared<CLI::App>("CLI App");
    return app;
}

int main(int argc, char *argv[]) {
    int result = 0;

    auto *driver = new PDDLDriver();

    string domain_file, problem_file;
    bool scanning_trace, parsing_trace;
    string algorithm, heuristic;

    auto app = setUpCLI(domain_file, problem_file,
                        scanning_trace, parsing_trace,
                        algorithm, heuristic);


    CLI11_PARSE(*app, argc, argv);

    if (scanning_trace) {
        driver->trace_scanning = true;
    }

    if (parsing_trace) {
        driver->trace_parsing = true;
    }

    if (!driver->parse(domain_file)) {
        cout << "Parsing " << domain_file << "... ";
        if (!result) cout << "ok!" << endl;
        else cout << "Error!" << endl;
    }

    if (!driver->parse(problem_file)) {
        cout << "Parsing " << problem_file << "... ";
        if (!result) cout << "ok!" << endl;
        else cout << "Error!" << endl;
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
    /*
    vector<Action *> *applicableActions = parserController.ApplicableActions(currentState);
    if (applicableActions->empty()) cout << "No applicable actions on this state";
    else {
        cout << "Applicable action(s): " << endl;
        for (unsigned int i = 0; i < applicableActions->size(); i++) {
            cout << applicableActions->at(i)->getName() << endl;
        }
    }
     */

    // Get states created by applying all applicable actions
    //vector<Action *> *applicableActions = parserController.ApplicableActions(currentState);
    //parserController.NextStates(currentState, applicableActions);


    // Hashing tests
    /*
    Hashing hash = Hashing();
    hash.CreateDictionaries(driver);
    hash.PrintNameDictionary();
    vector<string> objs = vector<string>();
    objs.push_back("move");
    objs.push_back("rooma");
    objs.push_back("roomb");
    hash.GetHashID(objs);
    hash.GetObjectsFromHash(104050);
     */



    // Run heuristics demo.
    HeuristicsDemo(parserController, currentState);

    if (driver) delete (driver);

    return result;
}

std::shared_ptr<CLI::App> setUpCLI(string &domain_file, string &problem_file,
                                   bool &scanning_trace, bool &parsing_trace,
                                   string &algorithm, string &heuristic) {

    // CLI::App app{APP_DESCRIPTION};
    std::shared_ptr<CLI::App> app = get_app();

    app->add_option("-d", domain_file, "Require an PDDL domain file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_option("-f", problem_file, "Require a PDDL problem file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_flag("-s", scanning_trace, "Tenable Scanning Trace");

    app->add_flag("-p", parsing_trace, "Tenable Parsing Trace");

    app->add_option("-a", algorithm, AVAILABLE_ALGORITHMS)
            ->required();

    app->add_option("-r", heuristic, AVAILABLE_HEURISTICS)
            ->required();

    return app;

}

void usage(char *filename) {
    cout << "usage: " << filename << " [-s] [-p] <domain.pddl> <problem.pddl>" << endl;
    cout << endl;
    cout << "OPTIONS:" << endl;
    cout << " -s\tenable scanning trace." << endl;
    cout << " -p\tenable parsing trace." << endl;
}
