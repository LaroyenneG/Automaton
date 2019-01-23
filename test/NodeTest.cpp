//
// Created by guillaume on 21/01/19.
//

#include <vector>
#include "NodeTest.h"

NodeTest::NodeTest(const std::string &string) : TestCase(string) {
}

void NodeTest::runTest() {

    std::vector<char> alphabet;
    alphabet.push_back('a');
    alphabet.push_back('c');
    alphabet.push_back('d');

    Node node(45);


    CPPUNIT_ASSERT(node.getId() == 45);
    CPPUNIT_ASSERT(node.getTransitions().empty());
    CPPUNIT_ASSERT(node.isOutput());
    CPPUNIT_ASSERT(node.next('a') == UNKNOWN_NODE_ID_VALUE);


    try {
        node.putTransition('a', UNKNOWN_NODE_ID_VALUE);
        CPPUNIT_FAIL("error");
    } catch (const std::string &str) {}


    node.putTransition('c', 1);

    CPPUNIT_ASSERT(!node.isOutput());

    node.markOutput();

    CPPUNIT_ASSERT(node.isOutput());

    node.unMarkOutput();

    CPPUNIT_ASSERT(!node.isOutput());

    node.removeNode(1);

    CPPUNIT_ASSERT(node.isOutput());
}


