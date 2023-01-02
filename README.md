# Containers
Repository is created to practice building project with:
 - Automated builds using Github workflows (building C++ project, running googletests, valgrind, sanitizers)
 - CMake build system

# Minimal requirements
 - CMake 3.24 installed [build project]
 - gcc 4.8 installed [gcov and sanitizers are included according to Readme: https://github.com/google/sanitizers/wiki/AddressSanitizer]
 - gcc 11.x installed [C++20 support is enabled in CMake build system: https://en.cppreference.com/w/cpp/compiler_support/20]
 - valgrind installed [to run valgrind check in similar way like in valgrind.yml]

# Recommended way of using CMake
 - To generate project: cmake -B build-dir -S project-dir
 - To compile generated project: cmake --build build-dir
 
 - Using additional functionality requires using flags when generating project:
   - Addess Sanitizers: cmake -B build-dir -S project-dir -DASan=ON
   - Leak Sanitizers: cmake -B build-dir -S project-dir -DLSan=ON

# How to run project
 - Linux: install CMake, gcc and editor of your choice and follow "Recommended way of using CMake" paragraph
 - Windows: install Visual Studio with C++ support (include CMake support for C++)

# Generating code-coverage locally
To generate code coverage using lcov you need to use linux OS and follow steps:
 - Generate project with 'COVERAGE' option included: cmake -B build-dir -S project-dir -DCOVERAGE=ON
 - Compile project: cmake --build build-dir
 - Navigate into build-dir and invoke: generate_code_coverage_raport.sh script
   - It will create new directory: code_coverage which will contain essential files.
   - Navigate into code_coverage directory and use your web-browser to inspect "index.html" file which will contain
     code-coverage for the project
