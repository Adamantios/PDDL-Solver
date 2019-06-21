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
                                   string &algorithm, string &heuristic,
                                   bool &debug_mode);

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
    bool scanning_trace = false, parsing_trace = false, debug_mode = false;

    auto app = setUpCLI(domain_file, problem_file,
                        scanning_trace, parsing_trace,
                        algorithm, heuristic,
                        debug_mode);

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
                                                  NULL);
    currentState->setDebug(debug_mode);
    StateWrapper *goalState = new StateWrapper(driver->problem->getGoal(),
                                               parserController,
                                               heuristicsController,
                                               NULL);

    if(*currentState >= *goalState || *goalState <= *currentState){
         cout << "This Problem is already solved." << endl;
         return result;
    }

    cout << "Press a button to start!\n";
    cin.ignore();

    long long mem,examined;
    cout << "================== CURRENT STATE ==================" << endl;
    cout << *currentState << endl;

    auto bsol = Astar(currentState, goalState, examined, mem);


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


    cout << "================== GOAL FOUND ==================" << endl;
    cout << *bsol << endl;

    return 0;
}

std::shared_ptr<CLI::App> setUpCLI(string &domain_file, string &problem_file,
                                   bool &scanning_trace, bool &parsing_trace,
                                   string &algorithm, string &heuristic,
                                   bool &debug_mode) {

    // CLI::App app{APP_DESCRIPTION};
    std::shared_ptr<CLI::App> app = get_app();

    app->add_option("--domain", domain_file, "Require an PDDL domain file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_option("--problem", problem_file, "Require a PDDL problem file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_flag("--scanning-trace", scanning_trace, "Tenable Scanning Trace");

    app->add_flag("--parsing-trace", parsing_trace, "Tenable Parsing Trace");

    app->add_flag("--debug", debug_mode, "Debug mode, Print in every step");

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
