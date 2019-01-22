//
// Created by guillaume on 20/01/19.
//

#ifndef AUTOMATON_NODE_H
#define AUTOMATON_NODE_H

#include <map>

#define UNKNOWN_NODE_ID_VALUE 0

class Node {

private:
    bool outNode;
    unsigned int id;
    std::map<char, unsigned int> transitions;
    const std::vector<char> &alphabet;

public:
    explicit Node(unsigned int _id, const std::vector<char> &_alphabet);

    Node(const Node &node);

    unsigned int getId() const;

    bool isOutput() const;

    void removeNode(unsigned int nodeId);

    void putTransition(char letter, unsigned int nodeId);

    const std::map<char, unsigned int> &getTransitions() const;

    void markOutput();

    void unMarkOutput();

    ~Node();

    unsigned int next(char letter) const;
};


#endif //AUTOMATON_NODE_H
