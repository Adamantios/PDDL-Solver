// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <heuristics_demo.h>
#include "pddldriver.hh"
#include "ParserController.h"
#include "hashing.h"
#include "CLI11.hpp"
#include "state_wrapper.h"
#include "algorithms.h"
using namespace std;

string APP_DESCRIPTION = "This application implements a pddl solver."; // Write More
string AVAILABLE_ALGORITHMS = "You can choose an algorithm among the following ones:\nA_STAR";
string AVAILABLE_HEURISTICS = "You can choose a heuristic among the following ones:\nMAX_COST";

void usage(char *filename);

std::shared_ptr<CLI::App> setUpCLI(string &domain_file, string &problem_file,
                                   bool &scanning_trace, bool &parsing_trace,
                                   bool &enable_debug,
                                   string &algorithm, string &heuristic);

std::shared_ptr<CLI::App> get_app() {
    auto app = std::make_shared<CLI::App>("CLI App");
    return app;
}

int main(int argc, char *argv[]) {
    int result = 0;

    auto *driver = new PDDLDriver();

    string domain_file, problem_file;

    string algorithm, heuristic;
    // Init Controller.
    ParserController *parserController = new ParserController(driver) ;
    Heuristics *heuristicsController = new Heuristics(parserController);
    bool scanning_trace = false, parsing_trace = false, enable_debug = false;

    auto app = setUpCLI(domain_file, problem_file,
                        scanning_trace, parsing_trace,
                        enable_debug,
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

    StateWrapper *currentState = new StateWrapper(driver->problem->getInit(),
                                                  parserController,
                                                  heuristicsController,
                                                  nullptr);
    currentState->setDebug(enable_debug);
    StateWrapper *goalState = new StateWrapper(driver->problem->getGoal(),
                                               parserController,
                                               heuristicsController,
                                               nullptr);

    long long mem,examined;

    auto bsol = Astar(currentState, goalState, examined, mem);

    cout<<"== Solution found in "<<bsol->getDepth()<<" moves =="<<endl;
    bsol->printActionsSequence();

    // if (driver) delete (driver);

    return 0;
}

std::shared_ptr<CLI::App> setUpCLI(string &domain_file, string &problem_file,
                                   bool &scanning_trace, bool &parsing_trace,
                                   bool &enable_debug,
                                   string &algorithm, string &heuristic) {

    // CLI::App app{APP_DESCRIPTION};
    std::shared_ptr<CLI::App> app = get_app();

    app->add_option("--domain", domain_file, "Require an PDDL domain file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_option("--problem", problem_file, "Require a PDDL problem file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_flag("-s", scanning_trace, "Tenable Scanning Trace");

    app->add_flag("-p", parsing_trace, "Tenable Parsing Trace");

    app->add_flag("--debug", enable_debug, "Enable verbose debug");

    app->add_option("-a", algorithm, AVAILABLE_ALGORITHMS)
            ->required();

    app->add_option("--heuristic", heuristic, AVAILABLE_HEURISTICS)
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
