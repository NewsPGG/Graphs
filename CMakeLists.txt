cmake_minimum_required(VERSION 3.10)
project(Graphs C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(src)

add_library(StatesLib STATIC
        src/graph/graph.c
        src/priorityQueue/PriorityQueue.c
)

add_executable(states src/main.c)
target_link_libraries(states StatesLib)

add_executable(test_states Tests/tests.c)
target_link_libraries(test_states StatesLib)