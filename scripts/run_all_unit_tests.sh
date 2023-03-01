#!/bin/bash

find_command="find"." -name '*test_suite' -type f"
test_to_run=($(eval "${find_command}"))

for test in ${test_to_run[@]}; do
	pushd ${test}
	echo "Running ${test} ..."
	./`basename ${test}`
	popd
done
