#!/usr/bin/python3

import subprocess

subprocess.run(['git', 'status'])
subprocess.run(['git', 'commit', '-am', '[Github Action] clang-format changes'])
subprocess.run(['git', 'push'])
