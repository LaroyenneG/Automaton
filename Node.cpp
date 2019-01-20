//
// Created by guillaume on 20/01/19.
//

#include <vector>
#include <map>
#include "Node.h"

Node::Node(int _id, const std::vector<char> &_alphabet) : id(_id), alphabet(_alphabet) {

}

int Node::getId() const {
    return id;
}

Node::~Node() {
    for (auto &transition : transitions) {
        delete transition.second;
    }
}

bool Node::isOutput() const {
    return transitions.empty();
}

void Node::removeNode(Node *node) {

    std::vector<char> toDelete;

    for (auto transition : transitions) {
        if (transition.second == node) {
            toDelete.push_back(transition.first);
            delete transition.second;
        }
    }

    for (auto transition : toDelete) {
        transitions.erase(transition);
    }
}

Node *Node::next(char c) const {

    auto it = transitions.find(c);
    if (it != transitions.end()) {
        return (*it).second;
    }

    return nullptr;
}

void Node::putTransition(char letter, Node *node) {

    bool find = false;

    for (auto &c: alphabet) {
        if (c == letter) {
            find = true;
            break;
        }
    }

    if (!find) {
        throw "un know letter";
    }


    transitions[letter] = node;
}

const std::map<char, Node *> &Node::getTransitions() const {
    return transitions;
}
