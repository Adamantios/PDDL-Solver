#include "pddldriver.hh"
#include <iostream>
#include <string>

;

void usage(char* filename);

int main(int argc, char* argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return -1;
    }

    int result = 0;

    PDDLDriver driver;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
            driver.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
            driver.trace_scanning = true;
        } else if (!driver.parse(argv[i])) {
            std::cout << "Parsing " << argv[i] << "... ";
            if (!result)
                std::cout << "ok!" << std::endl;
            else
                std::cout << "Error!" << std::endl;
        } else {
            result = -2;
            break;
        }
    }

    std::cout << std::endl;
    std::cout << *(driver.domain) << std::endl;
    std::cout << *(driver.problem) << std::endl;

    return result;
}

void usage(char* filename)
{
    std::cout << "usage: " << filename << " [-s] [-p] <domain.pddl> <problem.pddl>" << std::endl;
    std::cout << std::endl;
    std::cout << "Domain and problem PDDL parser in C/C++ using Flex & Bison." << std::endl;
    std::cout << "https://github.com/thiagopbueno/pddlparser-pp" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << " -s\tenable scanning trace." << std::endl;
    std::cout << " -p\tenable parsing trace." << std::endl;
}
