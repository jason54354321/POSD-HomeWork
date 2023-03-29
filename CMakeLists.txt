cmake_minimum_required(VERSION 3.10)
project(hello VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# header
include_directories(include)
include_directories(include/devices)

# src
file(GLOB_RECURSE SOURCE "src/*.cpp")
add_executable(hello ${SOURCE})
target_link_libraries(hello gtest_main)
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# tests
file(GLOB_RECURSE TEST "tests/*.cpp")
file(GLOB_RECURSE TEST_SOURCE "src/*.cpp")
list(FILTER TEST_SOURCE EXCLUDE REGEX "main.cpp$")
add_executable(hello_test ${TEST} ${TEST_SOURCE})
target_link_libraries(hello_test gtest_main gmock_main)
target_include_directories(hello_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 設定測試運行命令，可以使用 ctest 命令運行所有單元測試
enable_testing()
add_test(NAME hello_test COMMAND hello_test)
