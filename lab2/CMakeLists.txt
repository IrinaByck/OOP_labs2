cmake_minimum_required(VERSION 3.10)
project(decimal_lab)

set(CMAKE_CXX_STANDARD 17)

# Находим Google Test
find_package(GTest REQUIRED)

# Библиотека Decimal
add_library(decimal_lib src/decimal.cpp)
target_include_directories(decimal_lib PUBLIC include)

# Основная программа
add_executable(main_program main.cpp)
target_link_libraries(main_program decimal_lib)

# Тесты
add_executable(tests test/tests.cpp)
target_link_libraries(tests decimal_lib GTest::gtest GTest::gtest_main)
