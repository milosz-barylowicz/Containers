# Containers
Repository contains implementation of few STL like containers but main reason is to practice building build system and DevOps related skills.
Main focuses here are to:
1. Practice building project architecture with usage of CMake on different operating systems
2. Validate if code is able to be executed on different operating systems
3. Build simple CI architecture based on GitHub Actions (focusing on executing unit-tests and running various type of tools like Valgring or sanitizers)

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
 - Navigate into build-dir and invoke: ```generate_code_coverage_raport.sh``` script
   - It will create new directory: code_coverage which will contain essential files.
   - Navigate into code_coverage directory and use your web-browser to inspect ```index.html``` file which will contain
     code-coverage for the project

# Results of code-coverage pipeline
Code-coverage pipeline is creating code coverage report and deploying it on GitHub-pages. It can be found [here](https://milosz-barylowicz.github.io/Containers/)

# Using Valgrind (Linux)
To check if project contains any memory corrution issues Valgrind tool can be used.
1. Build project with CMake following **Recommended way of using CMake** paragraph
2. Execute command ```valgrind -s -v --error-exitcode=1 --leak-check=full <path-to-certain-unit-test-suite>```
3. After push or PR creation there is valgrind-pipeline that execute valgrind-tool to every test-suit automaticlly so there can be found raport in ```Running valgrind``` stage

# Using sanitizers (Linux)
To use sanitizers checks first of all project have to be build with additional flags:
1. For Addess Sanitizers: ```cmake -B <build-dir> -S <source-dir> -DASan=ON```
2. For Leak Sanitizers: ```cmake -B <build-dir> -S <source-dir> -DLSan=ON```
3. For UndefinedBehavior Sanitizer ```cmake -B <build-dir> -S <source-dir> -DUBSan=ON```

After successful build and tests execution there will be available logs with sanitizers output printed. More information about sanitizers can be found in officall [GitHub repository](https://github.com/google/sanitizers)

# Using Docker to compile and work with repository
Follow instructions [here](https://docs.docker.com/engine/install/ubuntu/) to install Docker on your Ubuntu distribution

After successful installation and setup of docker execute ```build_and_run_docker.sh``` script to build project and run all unit-tests. This method won't produce output directory.

## Manually building and running docker
1. To build docker image run ```docker build --tag containers-docker --build-arg UID=$(id -u) --build-arg GID=$(id -g) .```
2. To run previously builded image run ```docker run --user $(id -u):$(id -g) --rm --volume $(pwd):/workspace/containers:rw containers-docker /bin/bash```
