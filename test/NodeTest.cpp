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

    Node *node = new Node(45, alphabet);


    CPPUNIT_ASSERT(node->getId() == 45);
    CPPUNIT_ASSERT(node->getTransitions().empty());
    CPPUNIT_ASSERT(node->isOutput());
    CPPUNIT_ASSERT(node->next('a') == nullptr);

    try {
        node->next('z');
        CPPUNIT_FAIL("error");
    } catch (const std::string &str) {}

    try {
        node->putTransition('a', nullptr);
        CPPUNIT_FAIL("error");
    } catch (const std::string &str) {}


    node->putTransition('c', node);

    CPPUNIT_ASSERT(!node->isOutput());

    node->markOutput();

    CPPUNIT_ASSERT(node->isOutput());


    delete node;
}


