#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>

using namespace std;

struct Word {
    string name;
    string description;
};

ostream& operator<<(ostream& ost, const Word& word);

#endif // WORD_H
