# CMake generated Testfile for 
# Source directory: /home/ghann/GHGE
# Build directory: /home/ghann/GHGE/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RunTests "/usr/bin/cmake" "-E" "sh" "-c" "/home/ghann/GHGE/build/bin/tests | tee /home/ghann/GHGE/build/test_results.log")
set_tests_properties(RunTests PROPERTIES  _BACKTRACE_TRIPLES "/home/ghann/GHGE/CMakeLists.txt;70;add_test;/home/ghann/GHGE/CMakeLists.txt;0;")
