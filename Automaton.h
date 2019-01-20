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
    static std::mutex mutex;
    static int nodeCounter;

    std::vector<char> alphabet;

    std::list<Node *> nodes;

    Node *input;

    int nextId() const;

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
};


#endif //AUTOMATON_AUTOMATON_H
