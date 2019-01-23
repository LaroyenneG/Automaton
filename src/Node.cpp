//
// Created by guillaume on 20/01/19.
//

#include <vector>
#include <map>
#include "Node.h"
#include "Automaton.h"

Node::Node(unsigned int _id) : id(_id), outNode(false) {
}

Node::Node(const Node &node) : id(node.id), outNode(node.outNode), transitions(node.transitions) {

}

unsigned int Node::getId() const {
    return id;
}

Node::~Node() = default;

bool Node::isOutput() const {
    return transitions.empty() || outNode;
}

void Node::removeNode(unsigned int nodeId) {

    std::vector<char> linkToDelete;

    for (auto transition : transitions) {
        if (transition.second == nodeId) {
            linkToDelete.push_back(transition.first);
        }
    }

    for (auto letter : linkToDelete) {
        transitions.erase(letter);
    }
}

unsigned int Node::next(char letter) const {

    unsigned int id = UNKNOWN_NODE_ID_VALUE;

    auto it = transitions.find(letter);
    if (it != transitions.end()) {
        id = (*it).second;
    }

    return id;
}

void Node::putTransition(char letter, unsigned int nodeId) {

    if (nodeId == UNKNOWN_NODE_ID_VALUE) {
        throw std::string("invalid node id");
    }

    transitions[letter] = nodeId;
}

const std::map<char, unsigned int> &Node::getTransitions() const {
    return transitions;
}

void Node::markOutput() {
    outNode = true;
}

void Node::unMarkOutput() {
    outNode = false;
}


