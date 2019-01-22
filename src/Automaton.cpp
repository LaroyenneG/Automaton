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

Automaton::Automaton() : input(nullptr), nodeCounter(0) {
    input = generateNewNode();
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
    while (!nodes.empty()) {
        destroyNode(nodes.front());
    }
}

Node *Automaton::generateNewNode() {

    Node *node = new Node(nextNodeId(), alphabet);

    nodes.push_back(node);

    return node;
}

void Automaton::destroyNode(Node *node) {

    for (Node *&n : nodes) {
        n->removeNode(node);
    }

    nodes.remove(node);

    if (node == input) {
        input = nullptr;
    }

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

    if (invalidLetter || input == nullptr) {
        return false;
    }

    int index = 0;

    bool isExit = input->isOutput();

    Node *pNode = input;

    bool endTravel = false;

    while (index < word.size() && !endTravel) {

        isExit = pNode->isOutput();

        pNode = pNode->next(word[index]);

        endTravel = pNode == nullptr;

        if (!endTravel) {
            index++;
        }
    }

    return isExit && index == word.size();

}

const std::list<Node *> &Automaton::getNodes() const {
    return nodes;
}

Node *Automaton::getInput() const {
    return input;
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
