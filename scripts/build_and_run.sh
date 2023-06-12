#!/bin/bash

current_working_dir="workspace"

pushd `dirname ${current_working_dir}`
cmake -S `basename ${current_working_dir}`/containers -B `basename ${current_working_dir}`/build;
cmake --build `basename ${current_working_dir}`/build;
bash ./`basename ${current_working_dir}`/build/tests/run_all_unit_tests.sh
