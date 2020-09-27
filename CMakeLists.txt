cmake_minimum_required(VERSION 3.17)
project(parsing)

set(CMAKE_CXX_STANDARD 17)
include_directories(parsers .)

add_executable(parsing main.cpp parsers/pratt.h parsers/ll.h parsers/lr.h parsers/recursivedescent.h syntaxtree.h tokenizer.h)