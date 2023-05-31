#!/bin/bash

# run all unit tests to generate code coverage
cd tests;
./run_all_unit_tests.sh;
cd ..;

# installing lcov
sudo apt install lcov;

# runnning lcov
lcov -c -d . -o code-coverage.info --include *.cpp --include *.hpp;

# generating html

genhtml code-coverage.info --output-directory code_coverage;
