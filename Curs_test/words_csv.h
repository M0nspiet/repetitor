#ifndef WORDS_CSV_H
#define WORDS_CSV_H

#include <vector>
#include "word.h"

vector<Word> load_dictionary_from_csv(const string& filename);

#endif // WORDS_CSV_H
