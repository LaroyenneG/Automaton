cmake_minimum_required(VERSION 3.13)
project(Automaton)

set(CMAKE_CXX_STANDARD 17)


add_executable(Automaton
        src/Automaton.cpp
        src/Automaton.h
        src/Node.cpp
        src/Node.h test/main.cpp test/NodeTest.cpp test/NodeTest.h)

target_link_libraries(Automaton cppunit)
target_link_libraries(Automaton pthread)