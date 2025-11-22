cmake_minimum_required(VERSION 3.10)
project(decimal)

set(CMAKE_CXX_STANDARD 17)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(main main.cpp src/decimal.cpp)

# Тесты
add_executable(tests test/test_decimal.cpp src/decimal.cpp)
target_link_libraries(tests gtest_main)
