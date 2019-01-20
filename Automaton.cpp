//
// Created by guillaume on 20/01/19.
//

#include "Automaton.h"

std::mutex Automaton::mutex;

int Automaton::nodeCounter = 0;

int Automaton::nextId() const {

    mutex.lock();

    int id = nodeCounter++;

    mutex.unlock();

    return id;
}

Automaton::Automaton() : input(nullptr) {
    input = generateNewNode();
}

Automaton::operator std::string() const {

    std::string string = "Automaton";
    string.append(std::to_string(nodes.size()));

    return string;
}

void Automaton::addLetter(char c) {
    alphabet.push_back(c);
}

Automaton::~Automaton() {

    for (auto &node : nodes) {
        destroyNode(node);
    }
}

Node *Automaton::generateNewNode() {

    Node *node = new Node(nextId(), alphabet);

    nodes.push_back(node);

    return node;
}

void Automaton::destroyNode(Node *node) {

    nodes.remove(node);

    input->removeNode(node);

    delete node;
}

bool Automaton::operator==(const std::string &word) const {

    return recognize(word);
}

bool Automaton::recognize(const std::string &word) const {

    for (auto &c : word) {

        bool find = false;

        for (auto &l : alphabet) {
            if (l == c) {
                find = true;
                break;
            }
        }

        if (!find) {
            return false;
        }
    }

    int cursor = 0;

    Node *pNode = input;
    while (!pNode->isOutput()) {

        pNode = pNode->next(word[cursor]);
        if (pNode == nullptr) {
            return false;
        }

        cursor++;
    }

    return cursor == word.size();
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
