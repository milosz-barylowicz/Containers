# Containers
Repository contains implementation of few STL like containers but main reason is build skills of constructing scripts generating build systems using [CMake](https://cmake.org/) and basics of building CI/CD infrastructure.<br>

Tabble of content:
- [using Containers library in other projects](#using-containers-library-in-other-projects)
- [minimal requirements](#minimal-requirements)
- [how to run project](#how-to-run-project)
- [recommended way of using CMake on Linux](#recommended-way-of-using-cmake-linux)
- [generating code-coverage locally on Linux](#generating-code-coverage-locally-linux)
- [results of code-coverage pipeline](#results-of-code-coverage-pipeline)
- [using valgrind on Linux](#using-valgrind-linux)
- [using sanitizers on Linux](#using-sanitizers-linux)
- [using docker container](#using-docker-container)
    - [manually building and running docker](#manually-building-and-running-docker)
- [working with python scripts](#working-with-python-scripts)


# Using Containers library in other projects
To install and use Containers library in other C++ projects based on CMake there are need for two steps:
1. Add step for downloading this repository. Example of use:
```CMake
# Download Containers repository to testsing
include(FetchContent)
FetchContent_Declare(
    Containers
        GIT_REPOSITORY https://github.com/milosz-barylowicz/Containers.git
        GIT_TAG        main)
FetchContent_MakeAvailable(Containers)
```
2. Link downloaded library to executable that containers should be used. Example of use:
```CMake
# Linking Containers Library
target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        Containers)
```
3. Last thing is just use **#include** statemnet with container that is needed. Example:
```C++
#include <iostream>
#include "vector.hpp"

int main() {
    containers::Vector<int> numbers { 1, 2, 3, 4, 5, 6, 7 };
    std::cout << "numbers: ";
    for (const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

# Minimal requirements
 - CMake 3.24 installed [build project]
 - gcc 4.8 installed [gcov and sanitizers are included according to [sanitizers README](https://github.com/google/sanitizers/wiki/AddressSanitizer)]
 - gcc 11.x installed [C++20 support is enabled but compilers support can be found [here](https://en.cppreference.com/w/cpp/compiler_support/20)]

# How to run project
 - Linux: install CMake, gcc and editor of your choice and follow **Recommended way of using CMake** paragraph
 - Windows: install Visual Studio with C++ support (include CMake support for C++)

# Recommended way of using CMake (Linux)
 - To generate project: ```cmake -B <build-dir> -S <source-dir>```
 - To compile generated project: ```cmake --build <build-dir>```

# Generating code-coverage locally (Linux)
To generate code coverage using lcov you need to use linux OS and follow steps:
 - Generate project with 'COVERAGE' option included: ```cmake -B <build-dir> -S <source-dir> -DCOVERAGE=ON```
 - Compile project: ```cmake --build <build-dir>```
 - Install [**lcov**](https://github.com/linux-test-project/lcov) tool
 - Navigate into <build-dir> and invoke: ```generate_code_coverage.py``` script
   - It will create new directory: **code_coverage** which will contain essential files.
   - Navigate into **code_coverage** directory and use your web-browser to inspect ```index.html``` file which will contain code-coverage for the project

# Results of code-coverage pipeline
Code-coverage pipeline is creating code coverage report and deploying it on GitHub-pages. It can be found [here](https://milosz-barylowicz.github.io/Containers/)

# Using Valgrind (Linux)
To check if project contains any memory corrution issues [valgrind tool](https://valgrind.org/) can be used.<br>
1. Build project with CMake following **Recommended way of using CMake** paragraph
2. Execute command ```valgrind -s -v --error-exitcode=1 --leak-check=full <path-to-certain-unit-test-suite>```

# Using sanitizers (Linux)
To use sanitizers checks first of all project have to be build with additional flags:
1. For Addess Sanitizers: ```cmake -B <build-dir> -S <source-dir> -DASan=ON```
2. For Leak Sanitizers: ```cmake -B <build-dir> -S <source-dir> -DLSan=ON```
3. For UndefinedBehavior Sanitizer ```cmake -B <build-dir> -S <source-dir> -DUBSan=ON```

After successful build and tests execution there will be available logs with sanitizers output printed. More information about sanitizers can be found in officall [GitHub repository](https://github.com/google/sanitizers)

# Using docker container
Follow instructions [here](https://docs.docker.com/engine/install/ubuntu/) to install Docker on your Ubuntu distribution

After successful installation and setup of docker execute [```build_and_run.py```](https://github.com/milosz-barylowicz/Containers/blob/documentation-update/scripts/docker/build_and_run.py) script to build project and run all unit-tests. This method won't produce output directory.

## Manually building and running docker
1. To build docker image run ```docker build --tag containers-docker --build-arg UID=$(id -u) --build-arg GID=$(id -g) .```
2. To run previously builded image run ```docker run --user $(id -u):$(id -g) --rm --volume $(pwd):/workspace/containers:rw containers-docker /bin/bash```

# Working with python scripts
In repository there are planty of python scripts to execute. Recommended way to work with them is to create virtual environment for [**python3**](https://www.python.org/downloads/) by following instructions:
- install **python3.x** and **python3.x-venv** on OS
- create virtual environment by calling ```python3.x -m venv <name-of-local-venv>```
- activate virtual environment by calling ```source <name-of-local-venv>/bin/activate```
