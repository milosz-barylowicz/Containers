#!/usr/bin/python3

import os
import subprocess

home_dir = os.getcwd()

os.chdir('tests')
subprocess.run(['python', 'run_unit_tests.py'])

os.chdir(home_dir)

coverage_info = 'code-coverage.info'

subprocess.run([
    'lcov',
    '--directory', '.',
    '--capture',
    '--output-file', coverage_info,
    '--ignore-errors', 'mismatch'
], check=True)

subprocess.run([
    'lcov',
    '--extract', coverage_info,
    '*/include/*',
    '--output-file', coverage_info
], check=True)

subprocess.run([
    'lcov',
    '--remove', coverage_info,
    '*/gtest/*',
    '*/usr/*',
    '--output-file', coverage_info
], check=True)

subprocess.run([
    'genhtml', coverage_info,
    '--output-directory', 'code-coverage'
], check=True)
