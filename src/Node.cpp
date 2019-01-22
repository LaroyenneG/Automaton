//
// Created by guillaume on 20/01/19.
//

#include <vector>
#include <map>
#include "Node.h"
#include "Automaton.h"

Node::Node(unsigned int _id, const std::vector<char> &_alphabet) : id(_id), alphabet(_alphabet), outNode(false) {
}

unsigned int Node::getId() const {
    return id;
}

Node::~Node() = default;

bool Node::isOutput() const {
    return transitions.empty() || outNode;
}

void Node::removeNode(Node *node) {

    std::vector<char> toDelete;

    for (auto transition : transitions) {
        if (transition.second == node) {
            toDelete.push_back(transition.first);
        }
    }

    for (auto letter : toDelete) {
        transitions.erase(letter);
    }
}

Node *Node::next(char letter) const {

    if (!Automaton::letterIsInAlphabet(alphabet, letter)) {
        throw std::string("unknown letter");
    }

    Node *pNode = nullptr;

    auto it = transitions.find(letter);
    if (it != transitions.end()) {
        pNode = (*it).second;
    }

    return pNode;
}

void Node::putTransition(char letter, Node *node) {

    if (!Automaton::letterIsInAlphabet(alphabet, letter)) {
        throw std::string("unknown letter");
    }

    if (node == nullptr) {
        throw std::string("node can not be null");
    }

    transitions[letter] = node;
}

const std::map<char, Node *> &Node::getTransitions() const {
    return transitions;
}

void Node::markOutput() {
    outNode = true;
}

void Node::unmarkOutput() {
    outNode = false;
}
