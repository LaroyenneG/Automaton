//
// Created by guillaume on 21/01/19.
//

#include <iostream>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "AutomatonTest.h"

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : Automaton" << std::endl;
        exit(EXIT_FAILURE);
    }

    CppUnit::TextTestRunner runner;

    runner.addTest(new AutomatonTest("Automaton class test"));

    runner.run();

    return EXIT_SUCCESS;
}