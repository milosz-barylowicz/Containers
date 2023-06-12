#!/bin/bash

find_command="find "." -name '*test_suite' -type f"
test_to_run=($(eval "${find_command}"))

failed_tests="failed test cases: "
result="0"
for test in ${test_to_run[@]}; do
    pushd `dirname ${test}`
    echo "Running ${test}..."
    valgrind -s -v --error-exitcode=1 --leak-check=full ./`basename ${test}`
    if [ "$?" != "0" ]; then
        failed_tests+=" `basename ${test}`\n"
        result="1"
    fi
    popd
done

if [ "${result}" != "0" ]; then
    printf "${failed_tests}"
fi
exit "${result}"
