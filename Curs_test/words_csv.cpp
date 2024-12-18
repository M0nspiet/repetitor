#include "words_csv.h"
#include <sstream>
#include <fstream>

vector<Word> load_dictionary_from_csv(const string& filename){
    ifstream file(filename);
    vector<Word> words;

    if (!file.is_open()) {
        throw "Error opening file: " + filename;
    }

    string line, name, description;
    while (getline(file, line)) {
        stringstream ss(line);
        if (getline(ss, name, ';') && getline(ss, description)) {
            words.push_back({ .name = name, .description = description });
        }
    }

    return words;
}
