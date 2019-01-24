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


    for (char c = 'a'; c <= 'z'; c++) {
        automaton.addLetter(c);
    }

    CPPUNIT_ASSERT(automaton.getAlphabet().size() == 26);

    automaton.buildMatrix();

    CPPUNIT_ASSERT(!automaton.recognize("a"));

    automaton.markExit(0);

    CPPUNIT_ASSERT(automaton.recognize(""));

    automaton.putLink(0, 0, 'a');

    CPPUNIT_ASSERT(automaton.recognize("a"));
    CPPUNIT_ASSERT(automaton.recognize("aa"));
    CPPUNIT_ASSERT(automaton.recognize("aaa"));
    CPPUNIT_ASSERT(automaton.recognize("aaaaaa"));
    CPPUNIT_ASSERT(automaton.recognize(""));
    CPPUNIT_ASSERT(!automaton.recognize("b"));

    automaton.unMarkExit(0);

    CPPUNIT_ASSERT(!automaton.recognize("a"));
}
