#!/bin/bash

files_to_format=$(find -name '*.cpp' -type f -or -name '*.hpp' -type f -or -name '*.c' -type f -or -name '.h' -type f -or -name '*.hxx' -type f -or -name '*.cxx' -type f)

for file in ${files_to_format}; do
    if [ -f "${file}" ]; then
        echo "Formatting ${file} ..."
        clang-format --style=file -i ${file}
    fi
done
