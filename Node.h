//
// Created by guillaume on 20/01/19.
//

#ifndef AUTOMATON_NODE_H
#define AUTOMATON_NODE_H

#include <map>


class Node {

private:
    bool outNode;
    int id;
    std::map<char, Node *> transitions;
    const std::vector<char> &alphabet;

public:
    explicit Node(int _id, const std::vector<char> &_alphabet);

    int getId() const;

    bool isOutput() const;

    void removeNode(Node *node);

    void putTransition(char letter, Node *node);

    const std::map<char, Node *> &getTransitions() const;

    void markOutput();

    void unmarkOutput();

    ~Node();

    Node *next(char c) const;
};


#endif //AUTOMATON_NODE_H
