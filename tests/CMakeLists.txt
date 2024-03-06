cmake_minimum_required(VERSION 3.14)


# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)



# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

add_executable(
  hello_test2
  tests.cpp
)
target_link_libraries(
  hello_test2
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test2)