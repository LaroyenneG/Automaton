//
// Created by guillaume on 22/01/19.
//

#include "AutomatonTest.h"
#include "../src/Automaton.h"

AutomatonTest::AutomatonTest(const std::string &string) : TestCase(string) {
}

void AutomatonTest::runTest() {

    Automaton automaton;

    CPPUNIT_ASSERT(automaton.getAlphabet().empty());
    CPPUNIT_ASSERT(automaton.getNodes().size() == 1);
    CPPUNIT_ASSERT(automaton.getInput() != nullptr);


    for (char c = 'a'; c <= 'z'; c++) {
        automaton.addLetter(c);
    }

    CPPUNIT_ASSERT(automaton.getAlphabet().size() == 26);

    CPPUNIT_ASSERT(!automaton.recognize("a"));

    Node *nodes[10];
    for (Node *&n: nodes) {
        n = automaton.generateNewNode();
    }

    CPPUNIT_ASSERT(automaton.getNodes().size() == 11);


    CPPUNIT_ASSERT(automaton.recognize(""));
}
