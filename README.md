# PDDL Solver
**PDDL Solver** was developed as a University Project for the **Planning Chronoprogramming and Constraint Satisfactions** Lesson.

It is a general purpose solver which uses the [Planning Domain Definition Language (PDDL)](https://en.wikipedia.org/wiki/Planning_Domain_Definition_Language), in order to get problem descriptions and then tries to solve them, using a [Search Algorithm](https://en.wikipedia.org/wiki/Search_algorithm) and a [Heuristic Function](https://en.wikipedia.org/wiki/Heuristic_(computer_science)).  

The Solver uses an existing [PDDL Parser](https://github.com/thiagopbueno/pddlparser-pp), in order to parse the input files.

## Build Planner
`cmake build && make`

## Run Planner
The user can choose among the <b>A*, GBFS, IDA*</b> algorithms and a heuristics function between **Max Cost** and **Additive Cost**.  

`$ pddl_solver.exe --domain <domain_file_path> --problem <problem_file_path> -a <search_algorithm> --heuristic <heuristic_function>`

The `<search_algorithm>` can be one of the following strings:
- A_STAR
- GBFS
- IDA_STAR
- DFS

The `<heuristic_function>` can be one of the following strings:
- MAX_COST
- ADD_COST
