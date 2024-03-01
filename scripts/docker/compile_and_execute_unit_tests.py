#!/usr/bin/python3

import os
import subprocess

current_working_dir = "workspace"

subprocess.run(['cmake', '-S', current_working_dir + "/containers", '-B', current_working_dir + "/build"])
subprocess.run(['cmake', '--build', current_working_dir + '/build'])

os.chdir(current_working_dir + '/build/tests/')
subprocess.run(['python3', 'run_unit_tests.py'])
