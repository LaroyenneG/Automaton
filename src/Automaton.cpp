//
// Created by guillaume on 20/01/19.
//

#include "Automaton.h"

unsigned int Automaton::nextNodeId() {

    mutex.lock();

    unsigned int id = nodeCounter++;

    mutex.unlock();

    return id;
}

Automaton::Automaton() : inputNodeId(UNKNOWN_NODE_ID_VALUE), nodeCounter(1) {
    inputNodeId = generateNewNode();
}

Automaton::Automaton(const Automaton &automaton) : inputNodeId(automaton.inputNodeId),
                                                   nodeCounter(automaton.nodeCounter), alphabet(automaton.alphabet) {
    for (auto &it : nodes) {
        nodes[it.first] = new Node(*it.second);
    }
}

Automaton::operator std::string() const {

    std::string string = "Automaton(";
    string.append(std::to_string(nodes.size()));
    string.append(")");

    return string;
}

void Automaton::addLetter(char c) {
    alphabet.push_back(c);
}

Automaton::~Automaton() {

    auto mapNodeCopy = nodes;

    for (auto &pair : mapNodeCopy) {
        destroyNode(pair.first);
    }
}

unsigned int Automaton::generateNewNode() {

    auto id = nextNodeId();

    nodes[id] = new Node(id, alphabet);

    return id;
}

void Automaton::destroyNode(unsigned int nodeId) {

    Node *node = getNode(nodeId);

    for (auto &pair : nodes) {
        pair.second->removeNode(nodeId);
    }

    if (nodeId == inputNodeId) {
        inputNodeId = UNKNOWN_NODE_ID_VALUE;
    }

    nodes.erase(nodeId);

    delete node;
}

bool Automaton::operator==(const std::string &word) const {

    return recognize(word);
}

bool Automaton::recognize(const std::string &word) const {

    bool invalidLetter = false;

    for (auto &letter : word) {
        if (!letterIsInAlphabet(alphabet, letter)) {
            invalidLetter = true;
            break;
        }
    }

    if (invalidLetter || inputNodeId == UNKNOWN_NODE_ID_VALUE) {
        return false;
    }


    Node *inputNode = getInput();

    int index = 0;

    bool isExit = inputNode->isOutput();

    Node *pNode = inputNode;

    bool endTravel = false;

    while (index < word.size() && !endTravel) {

        isExit = pNode->isOutput();

        unsigned int nodeId = pNode->next(word[index]);

        endTravel = nodeId == UNKNOWN_NODE_ID_VALUE;

        if (!endTravel) {
            index++;
            pNode = getNode(nodeId);
        }
    }

    return isExit && index == word.size();
}

Node *Automaton::getInput() const {
    return getNode(inputNodeId);
}

const std::vector<char> &Automaton::getAlphabet() const {
    return alphabet;
}

bool Automaton::letterIsInAlphabet(const std::vector<char> &alphabet, char letter) {

    bool find = false;

    for (auto &c: alphabet) {
        if (c == letter) {
            find = true;
            break;
        }
    }

    return find;
}

Node *Automaton::getNode(unsigned int id) const {

    Node *node = nullptr;

    auto pair = nodes.find(id);
    if (pair != nodes.end()) {
        node = (*pair).second;
    } else {
        throw std::string("invalid node id");
    }

    return node;
}

void Automaton::putAllNodeId(std::vector<unsigned int> &ids) const {
    for (auto &pair: nodes) {
        ids.push_back(pair.first);
    }
}

unsigned int Automaton::nodeNumber() const {
    return static_cast<unsigned int>(nodes.size());
}


