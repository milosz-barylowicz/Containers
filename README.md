# Containers
Repository is created to practice building project with:
 - Automated builds using Github workflows (building C++ project, running googletests, valgrind, sanitizers)
 - CMake build system

# Minimal requirements
 - CMake 3.24 installed [build project]
 - gcc 4.8 installed [gcov and sanitizers are included according to Readme: https://github.com/google/sanitizers/wiki/AddressSanitizer]
 - gcc 11.x installed [C++20 support is enabled in CMake build system: https://en.cppreference.com/w/cpp/compiler_support/20]

# Recommended way of using CMake
 - To generate project: cmake -B <build-dir> -S <project-dir>
 - To compile generated project: cmake --build build
 
 - Using additional functionality requires using flags when generating project:
   - Addess Sanitizers: cmake -B <<build-dir>> -S <project-dir> -ASan=ON
   - Leak Sanitizers: cmake -B <build-dir> -S <project-dir> -LSan=ON
