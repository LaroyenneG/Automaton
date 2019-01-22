//
// Created by guillaume on 20/01/19.
//

#ifndef AUTOMATON_AUTOMATON_H
#define AUTOMATON_AUTOMATON_H

#include <list>
#include <vector>
#include <mutex>
#include "Node.h"

class Automaton {

private:
    std::mutex mutex;
    unsigned int nodeCounter;

    std::vector<char> alphabet;

    std::list<Node *> nodes;

    Node *input;

    unsigned int nextNodeId();

public:
    explicit Automaton();

    void addLetter(char c);

    explicit operator std::string() const;

    Node *generateNewNode();

    void destroyNode(Node *node);

    Node *getInput() const;

    const std::list<Node *> &getNodes() const;

    const std::vector<char> &getAlphabet() const;

    bool recognize(const std::string &word) const;

    ~Automaton();

    bool operator==(const std::string &word) const;

    static bool letterIsInAlphabet(const std::vector<char> &alphabet, char letter);
};


#endif //AUTOMATON_AUTOMATON_H
