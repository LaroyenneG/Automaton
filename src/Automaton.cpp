//
// Created by guillaume on 20/01/19.
//

#include "Automaton.h"


Automaton::Automaton() : height(MINIMUM_NODE), matrix(nullptr),
                         width(MINIMUM_ALPHABET), built(false) {

}

Automaton::Automaton(const Automaton &automaton) : alphabet(automaton.alphabet), height(automaton.height),
                                                   width(automaton.width), built(automaton.built),
                                                   matrix(allocate(automaton.width, automaton.height)) {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = automaton.matrix[i][j];
        }
    }
}

int **Automaton::allocate(unsigned int x, unsigned int y) {

    auto **table = new int *[y];
    for (int i = 0; i < y; ++i) {
        table[i] = new int[x];
        for (int j = 0; j < x; ++j) {
            table[i][j] = EMPTY_NODE;
        }
    }

    return table;
}

Automaton::~Automaton() {
    if (built) {
        freeMatrix(matrix, height);
    }
}

void Automaton::addLetter(char letter) {

    if (built) {
        throw std::string("cannot add a letter after matrix's building");
    }

    if (letterIsInAlphabet(alphabet, letter)) {
        return;
    }

    alphabet.push_back(letter);

    width = static_cast<unsigned int>(alphabet.size() + 1);
}

const std::vector<char> &Automaton::getAlphabet() const {
    return alphabet;
}

bool Automaton::letterIsInAlphabet(const std::vector<char> &alphabet, char letter) {

    for (auto &l : alphabet) {
        if (l == letter) {
            return true;
        }
    }

    return false;
}

void Automaton::addNode() {

    if (!built) {
        throw std::string("matrix is not built");
    }

    auto oldMatrix = matrix;
    auto oldHeight = height;

    height++;

    matrix = new int *[height];

    for (int i = 0; i < oldHeight; ++i) {
        matrix[i] = oldMatrix[i];
    }

    for (int i = 0; i < width; ++i) {
        matrix[oldHeight][i] = EMPTY_NODE;
    }

    delete[] oldMatrix;
}

bool Automaton::recognize(const std::string &word) const {

    if (!built) {
        throw std::string("matrix is not built");
    }

    int counter = 0;
    int node = 0;

    for (char letter : word) {

        for (int c = 0; c < alphabet.size(); ++c) {

            if (letter == alphabet[c]) {

                int next = matrix[node][c];

                if (next != EMPTY_NODE) {
                    node = next;
                    counter++;
                    break;
                }
            }
        }
    }

    return counter == word.size() && matrix[node][width - 1] == EXIT_NODE;
}

void Automaton::putLink(unsigned int src, unsigned int dst, char letter) {

    if (!built) {
        throw std::string("matrix is not built");
    }

    if (src >= height || dst >= height) {
        throw std::string("invalid node id");
    }

    int index = -1;

    for (int i = 0; i < alphabet.size(); i++) {
        if (alphabet[i] == letter) {
            index = i;
        }
    }

    if (index < 0) {
        throw std::string("invalid letter");
    }

    matrix[src][index] = dst;
}

Automaton &Automaton::operator=(const Automaton &automaton) {

    if (built) {
        freeMatrix(matrix, height);
    }

    height = automaton.height;
    width = automaton.width;
    built = automaton.built;

    if (built) {

        matrix = allocate(width, height);

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                matrix[i][j] = automaton.matrix[i][j];
            }
        }
    }

    return *this;
}

void Automaton::buildMatrix() {

    if (built) {
        throw std::string("cannot rebuild matrix");
    }

    matrix = allocate(width, height);

    built = true;
}


void Automaton::detroydMatrix() {

    if (!built) {
        throw std::string("cannot destroy matrix");
    }

    freeMatrix(matrix, height);

    built = false;
}

void Automaton::freeMatrix(int **matrix, unsigned int height) {

    for (int i = 0; i < height; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void Automaton::markExit(unsigned int node) {

    if (!built) {
        throw std::string("matrix is not built");
    }

    if (node >= height) {
        throw std::string("invalid node id");
    }

    matrix[node][width - 1] = EXIT_NODE;
}

void Automaton::unMarkExit(unsigned int node) {

    if (!built) {
        throw std::string("matrix is not built");
    }

    if (node >= height) {
        throw std::string("invalid node id");
    }

    matrix[node][width - 1] = EMPTY_NODE;
}





