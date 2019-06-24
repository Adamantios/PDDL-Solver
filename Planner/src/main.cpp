#include <iostream>
#include <ctime>
#include "pddldriver.hh"
#include "utils.h"
#include "CLI11.hpp"
#include "state_wrapper.h"
#include "algorithms.h"

using namespace std;

std::shared_ptr<CLI::App> GetApp() {
    auto app = std::make_shared<CLI::App>("CLI App");
    return app;
}

std::shared_ptr<CLI::App> SetUpCli(string &domain_file, string &problem_file,
                                   bool &scanning_trace, bool &parsing_trace,
                                   bool &enable_debug,
                                   string &algorithm, string &heuristic) {
    string app_description = "This application implements a pddl solver. Requires domain and problem files in PDDL. "
                             "Max Cost/Additive Cost heuristics. A*, GBFS, IDA*, DFS search functions.";
    string available_algorithms = "You can choose an algorithm among the following ones:\n"
                                  "A_STAR | GBFS | IDA_STAR | DFS";
    string available_heuristics = "You can choose a heuristic among the following ones:\n"
                                  "MAX_COST | ADD_COST";

    // TODO CLI::App app{app_description};
    std::shared_ptr<CLI::App> app = GetApp();

    app->add_option("--domain", domain_file, "Require an PDDL domain file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_option("--problem", problem_file, "Require a PDDL problem file")
            ->required()
            ->check(CLI::ExistingFile);

    app->add_flag("-s", scanning_trace, "Tenable Scanning Trace");

    app->add_flag("-p", parsing_trace, "Tenable Parsing Trace");

    app->add_flag("--debug", enable_debug, "Enable verbose debug");

    app->add_option("-a", algorithm, available_algorithms)
            ->required();

    app->add_option("--heuristic", heuristic, available_heuristics)
            ->required();

    return app;
}

/**
 * Parse PDDL.
 * @param driver the PDDL parser driver.
 */
void ParsePddl(PDDLDriver *driver, bool scanning_trace, bool parsing_trace,
               const string &domain_file, const string &problem_file) {
    if (scanning_trace)
        driver->trace_scanning = true;

    if (parsing_trace)
        driver->trace_parsing = true;

    if (!driver->parse(domain_file))
        cout << "Parsing " << domain_file << "... ";
    cout << "ok!" << endl;

    if (!driver->parse(problem_file))
        cout << "Parsing " << problem_file << "... ";
    cout << "ok!" << endl;
}

Heuristics *ChooseHeuristics(const string &heuristic, Utils *utils) {
    Heuristics *heuristics;

    if (heuristic == "MAX_COST")
        heuristics = new Heuristics(utils, MAX_COST);
    else if (heuristic == "ADD_COST")
        heuristics = new Heuristics(utils, ADDITIVE_COST);
    else
        heuristics = new Heuristics(utils, MAX_COST);

    return heuristics;
}

StateWrapper *ChooseAndRunSolver(StateWrapper *current_state, StateWrapper *goal_state, const string &algorithm) {
    long long mem, examined;

    if (algorithm == "A_STAR")
        return Astar(current_state, goal_state, examined, mem);
    else if (algorithm == "GBFS")
        return BFS(current_state, goal_state, examined, mem);
    else if (algorithm == "IDA_STAR")
        return IDAstar(current_state, goal_state, examined, mem);
    else if (algorithm == "DFS")
        return DFS(current_state, goal_state, examined, mem);
    else
        return Astar(current_state, goal_state, examined, mem);
}

void ShowResults(StateWrapper *bsol, clock_t c_start, clock_t c_end) {
    // Print results.
    cout << "== Solution found in " << bsol->GetDepth() << " moves ==" << endl;
    bsol->printActionsSequence();
    cout << endl;

    // Print elapsed time.
    double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    cout << "CPU time used: " << time_elapsed_ms << " ms\n";
}

void SolvePddlProblem(PDDLDriver *driver, const string &algorithm, const string &heuristic, bool enable_debug) {
    // Init Utils and Heuristics Controller.
    auto *utils = new Utils(driver);
    Heuristics *heuristics = ChooseHeuristics(heuristic, utils);

    // Init current state.
    auto *current_state = new StateWrapper(driver->problem->getInit(), utils, heuristics, nullptr);
    // Set debug status.
    current_state->setDebug(enable_debug);
    // Init Goal.
    auto *goal_state = new StateWrapper(driver->problem->getGoal(), utils, heuristics, nullptr);

    // Run and time solver.
    clock_t c_start = clock();
    StateWrapper *bsol = ChooseAndRunSolver(current_state, goal_state, algorithm);
    clock_t c_end = clock();

    ShowResults(bsol, c_start, c_end);
}

int main(int argc, char *argv[]) {
    string domain_file, problem_file;
    string algorithm, heuristic;
    bool scanning_trace = false, parsing_trace = false, enable_debug = false;

    auto app = SetUpCli(domain_file, problem_file, scanning_trace, parsing_trace, enable_debug, algorithm, heuristic);
    CLI11_PARSE(*app, argc, argv)
    auto *driver = new PDDLDriver();
    ParsePddl(driver, scanning_trace, parsing_trace, domain_file, problem_file);
    SolvePddlProblem(driver, algorithm, heuristic, enable_debug);

    return 0;
}
