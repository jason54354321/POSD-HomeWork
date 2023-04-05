# CMake generated Testfile for 
# Source directory: D:/aaMyCode/hw1
# Build directory: D:/aaMyCode/hw1/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(hello_test "D:/aaMyCode/hw1/build/hello_test.exe")
set_tests_properties(hello_test PROPERTIES  _BACKTRACE_TRIPLES "D:/aaMyCode/hw1/CMakeLists.txt;39;add_test;D:/aaMyCode/hw1/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
