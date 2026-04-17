cmake_minimum_required(VERSION 3.10)
project(StatesProject C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wall")

add_library(StatesLib STATIC
        src/graph/graph.c
        src/priorityQueue/priorityQueue.c
)

add_executable(states src/main.c)
target_link_libraries(states StatesLib)

add_executable(test_states Tests/tests.c)
target_link_libraries(test_states StatesLib)

enable_testing()
add_test(NAME StateLogicTest COMMAND test_states)