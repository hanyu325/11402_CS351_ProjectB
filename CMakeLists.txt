cmake_minimum_required(VERSION 3.10)

project(CS351_ProjectB)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    QueryEngine
    Query_Engine.cpp
)

configure_file(
    ${CMAKE_SOURCE_DIR}/input.csv
    ${CMAKE_BINARY_DIR}/input.csv
    COPYONLY
)