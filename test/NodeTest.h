//
// Created by guillaume on 21/01/19.
//

#ifndef AUTOMATON_NODETEST_H
#define AUTOMATON_NODETEST_H

#include <cppunit/TestCase.h>
#include "../src/Node.h"

class NodeTest : public CppUnit::TestCase {

public:
    explicit NodeTest(const std::string &string);

    void runTest() override;
};


#endif //AUTOMATON_NODETEST_H
