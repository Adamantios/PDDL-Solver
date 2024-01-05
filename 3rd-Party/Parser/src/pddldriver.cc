#include "pddldriver.hh"
#include "pddlparser.tab.hh"

;

PDDLDriver::PDDLDriver()
{
    trace_parsing = trace_scanning = false;
    domain = nullptr;
    problem = nullptr;
}

PDDLDriver::~PDDLDriver()
{
    delete domain;
    delete problem;
}

int PDDLDriver::parse(const std::string& f)
{
    file = f;
    scan_begin();
    yy::PDDLParser parser(*this);
    parser.set_debug_level(trace_parsing);
    result = parser.parse();
    scan_end();
    return result;
}

void PDDLDriver::error(const yy::location& l, const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void PDDLDriver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}
