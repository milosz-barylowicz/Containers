#!/usr/bin/python3

import subprocess

files_to_format = subprocess.run(['find', '-name', '*.cpp', '-type', 'f',
                                  '-or' ,'-name', '*.hpp', '-type', 'f',
                                  '-or' ,'-name', '*.h', '-type', 'f',
                                  '-or' ,'-name', '*.c', '-type', 'f',
                                  '-or' ,'-name', '*.hxx', '-type', 'f',
                                  '-or' ,'-name', '*.cxx', '-type', 'f'], capture_output=True)

for file in files_to_format.stdout.split():
    print(f"pricessing file: {file}")
    subprocess.run(['clang-format', '--style=file', '-i', file])
