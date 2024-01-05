#!/usr/bin/env python3

import os
import subprocess
import argparse


def run_tests(dir, domain, problem, algorithm, heuristic):
    domain_path = os.path.join("data", "domains", f"{domain}.pddl")
    problem_path = os.path.join("data", "problems", domain, problem)
    
    command = os.path.join(dir, "pddl_solver")

    cmd = f"{command} --domain {domain_path} --problem {problem_path} -a {algorithm} --heuristic {heuristic}"
    print(cmd)
    print(subprocess.getoutput(cmd))


def run_grid(directory):

    problems = {}

    data_path = os.path.join(directory, "data", "problems")
    print(data_path)
    
    assert os.path.exists(data_path), f"Directory {data_path} does not exist"
    
    for dirpath, _, filenames in os.walk(data_path):
        print(dirpath)
        for filename in filenames:
            if filename.endswith(".pddl"):
                domain = os.path.basename(dirpath)
                if domain not in problems:
                    problems[domain] = []
                problems[domain].append(filename)
                
    algorithms = ["A_STAR", "GDFS", "IDA_STAR", "DFS", "BEST_FS"]
    heuristics = ["MAX_COST", "ADD_COST"]

    for domain in problems:
        for problem in problems[domain]:
            print("Problem", problem)
            for algorithm in algorithms:
                for heuristic in heuristics:
                    run_tests(directory, domain, problem, algorithm, heuristic)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--directory", help="Directory of the executable")
    args = parser.parse_args()
    run_grid(args.directory)
