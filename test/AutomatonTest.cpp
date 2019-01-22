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
    for (auto &n: nodes) {
        n = automaton.generateNewNode();
    }

    CPPUNIT_ASSERT(automaton.getNodes().size() == 11);


    CPPUNIT_ASSERT(automaton.recognize(""));

    Node *input = automaton.getInput();
    input->putTransition('a', input);
    input->markOutput();

    CPPUNIT_ASSERT(automaton.recognize("a"));
    CPPUNIT_ASSERT(automaton.recognize("aa"));
    CPPUNIT_ASSERT(automaton.recognize("aaa"));
    CPPUNIT_ASSERT(automaton.recognize("aaaaaa"));
    CPPUNIT_ASSERT(automaton.recognize(""));
    CPPUNIT_ASSERT(!automaton.recognize("b"));

    automaton.destroyNode(input);
    CPPUNIT_ASSERT(!automaton.recognize("a"));
}
