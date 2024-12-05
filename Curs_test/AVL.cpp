#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include "AVL.h"

ostream& operator<<(ostream& ost, const Word& word) {
    ost << word.name << " - " << word.description;
    return ost;
}

void load_dictionary_from_csv(const string& filename, AvlTree<Word>& Avl_tree){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line, name, description;
    while (getline(file, line)) {
        stringstream ss(line);
        if (getline(ss, name, ';') && getline(ss, description)) {
            Avl_tree.add({ .name = name, .description = description });
        }
    }
    file.close();
}