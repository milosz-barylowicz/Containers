#!/usr/bin/python3

import os
import argparse
import subprocess

def parse_arguments():
    args_parser = argparse.ArgumentParser(description='Pass user informations')
    args_parser.add_argument('--user', '-u', type=str, required=True)
    args_parser.add_argument('--group', '-g', type=str, required=True)

    return args_parser.parse_args()

def build(user, group):
    subprocess.run(['docker', 'build', '--tag', "containers-docker", '--build-arg', "UID=" + user, '--build-arg', "GID=" + group, os.getcwd()])

def run(user, group):
    docker_start_up_command = "/bin/bash"
    subprocess.run(['docker', 'run', '--user', user + ":" + group, '--rm', '--volume', os.getcwd() + ":/workspace/containers:rw", "containers-docker", docker_start_up_command])

if __name__ == "__main__":
    parameters = parse_arguments()
    build(parameters.user, parameters.group)
    run(parameters.user, parameters.group)
