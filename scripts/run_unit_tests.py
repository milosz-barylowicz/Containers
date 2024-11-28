#!/usr/bin/python3

import os
import subprocess

rootdir = '.'

for directory in os.listdir(rootdir):
    test_dir = directory
    if test_dir.endswith('test_suite'):
        home_dir = os.getcwd()
        os.chdir(test_dir)

        subprocess.run(['ctest', '-C', 'Debug', '--verbose'])
        os.chdir(home_dir)
