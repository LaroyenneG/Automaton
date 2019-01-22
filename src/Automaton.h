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

    std::map<unsigned int, Node *> nodes;

    unsigned int inputNodeId;

    unsigned int nextNodeId();

public:
    explicit Automaton();

    Automaton(const Automaton &automaton);

    void addLetter(char c);

    explicit operator std::string() const;

    unsigned int generateNewNode();

    void destroyNode(unsigned int nodeId);

    Node *getInput() const;

    const std::vector<char> &getAlphabet() const;

    bool recognize(const std::string &word) const;

    Node *getNode(unsigned int id) const;

    void putAllNodeId(std::vector<unsigned int> &ids) const;

    ~Automaton();

    bool operator==(const std::string &word) const;

    static bool letterIsInAlphabet(const std::vector<char> &alphabet, char letter);
};


#endif //AUTOMATON_AUTOMATON_H
