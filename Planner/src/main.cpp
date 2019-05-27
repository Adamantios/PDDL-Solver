// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
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

    PDDLDriver *driver = new PDDLDriver();
    ParserController parserController;

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
    parserController = ParserController(driver);
    // Test with print function
    parserController.Print();
    parserController.PrintPredicates();

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
