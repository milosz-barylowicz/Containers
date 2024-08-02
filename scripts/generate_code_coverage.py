#!/usr/bin/python3

import os
import subprocess

home_dir = os.getcwd()

os.chdir('tests')
subprocess.run(['python', 'run_unit_tests.py'])

os.chdir(home_dir)
subprocess.run(['lcov', '-c', '-d', '.', '-o', 'code-coverage.info', '--include', '*.cpp', '--include', '*.hpp', '--ignore-errors', 'mismatch'])
subprocess.run(['genhtml', 'code-coverage.info', '--output-directory', 'code_coverage'])
