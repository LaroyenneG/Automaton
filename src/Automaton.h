//
// Created by guillaume on 20/01/19.
//

#ifndef AUTOMATON_AUTOMATON_H
#define AUTOMATON_AUTOMATON_H

#include <list>
#include <vector>
#include <mutex>

#define MINIMUM_NODE 1
#define MINIMUM_ALPHABET 1
#define EMPTY_NODE -5
#define EXIT_NODE -6

class Automaton {

private:
    std::vector<char> alphabet;
    int **matrix;
    unsigned int width;
    unsigned int height;

    bool built;

    static int **allocate(unsigned int x, unsigned int y);

    static void freeMatrix(int **matrix, unsigned int height);

public:
    explicit Automaton();

    Automaton(const Automaton &automaton);

    void addLetter(char letter);

    const std::vector<char> &getAlphabet() const;

    void addNode();

    bool recognize(const std::string &word) const;

    void putLink(unsigned int src, unsigned int dst, char letter);

    void markExit(unsigned int node);

    void unMarkExit(unsigned int node);

    void buildMatrix();

    void detroydMatrix();

    ~Automaton();

    Automaton &operator=(const Automaton &automaton);

    static bool letterIsInAlphabet(const std::vector<char> &alphabet, char letter);
};


#endif //AUTOMATON_AUTOMATON_H
