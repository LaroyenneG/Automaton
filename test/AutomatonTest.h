//
// Created by guillaume on 22/01/19.
//

#ifndef AUTOMATON_AUTOMATONTEST_H
#define AUTOMATON_AUTOMATONTEST_H


#include <cppunit/TestCase.h>

class AutomatonTest : public CppUnit::TestCase {

public:
    explicit AutomatonTest(const std::string &string);

    void runTest() override;
};


#endif //AUTOMATON_AUTOMATONTEST_H
