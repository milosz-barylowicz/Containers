#!/usr/bin/python3

import os
import subprocess

root_dir = '.'

for directory in os.listdir(root_dir):
    test_dir = directory
    if test_dir.endswith('test_suite'):
        home_dir = os.getcwd()
        os.chdir(test_dir)

        subprocess.run(['valgrind', '-s', '-v', '--error-exitcode=1', '--leak-check=full', './' + test_dir])
        os.chdir(home_dir)
