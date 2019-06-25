import os
# domains = ['blocks', 'depot', 'ferry', 'gripper', 'typeworld']
domains = ['gripper']

problems = {}

name = [name for name in os.walk("./data/problems/") ]

for domain in domains:
    files = [x[2] for x in os.walk("./data/problems/{}".format(domain))]
    for file in files:
        problems[domain] = file
print(problems)
algorithms = ['A_STAR', 'GDFS', 'IDA_STAR', 'DFS', 'BEST_FS' ]
algorithms = ['A_STAR']

heuristics = ['MAX_COST', 'ADD_COST']

for domain in problems:
    for problem in problems[domain]:
        print("Problem", problem)
        for algorithm in algorithms:
            for heuristic in heuristics:
                cmd = "./Planner/pddl_solver --domain data/domains/{}.pddl --problem data/problems/{}/{} -a {} --heuristic {}".format(domain, domain, problem, algorithm, heuristic)
                print(cmd)
                print(os.popen(cmd).read())
