cmake_minimum_required(VERSION 3.10)
project(ClosestPairTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# путь к Gtest
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest)

# добавляем GTest
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest)

# Находим потоки
find_package(Threads REQUIRED)

# библиотека с реализацией
add_library(closest_pair_lib closest_pair.cpp)

# exe для тестов
add_executable(closest_pair_tests test_closest_pair.cpp)

# exe ручного ввода
add_executable(closest_pair_interactive main.cpp)

# для тестов
target_link_libraries(closest_pair_tests
        closest_pair_lib
        gtest
        gtest_main
        Threads::Threads
)

# для ручного ввода
target_link_libraries(closest_pair_interactive
        closest_pair_lib
)

# тесты
enable_testing()
add_test(NAME ClosestPairAllTests COMMAND closest_pair_tests)