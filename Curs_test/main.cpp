#include "AVL.h"
#include "word.h"
#include "words_csv.h"
#include <chrono>

#include "double_hashing.h"

void use_AVL(vector<Word>& unsorted_words){
    AvlTree<Word> tree([](const Word& a, const Word& b) { return a.name < b.name; });

    auto begin = std::chrono::steady_clock::now();
    for (auto& word : unsorted_words) {
        tree.add(word);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The insert time (AVL): " << elapsed_ms.count() << " ms\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i) {
        tree.search(unsorted_words[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The search 100000 values in (AVL): " << elapsed_ms.count() << " ms\n";
}

int hash_code_1(const Word& word, int n) {
    if (word.name.empty()) {
        return 0;
    }
    if (word.name.length() == 1) {
        return word.name[0];
    }
    if (word.name.length() == 2) {
        return (word.name[0]*word.name[1]) % n;
    }
    return (word.name[0]*word.name[1]*word.name[2]) % n;
}

int hash_code_2(const Word& word, int n) {
    return 1 + hash_code_1(word, n-1);
}

bool is_equal_name(const Word& lhs, const Word& rhs) {
    return lhs.name == rhs.name;
}

void use_hasing(vector<Word>& unsorted_words){
    const size_t size = 200000;
    DoubleHashTable<Word> hash_table(size, hash_code_1, hash_code_2, is_equal_name);

    auto begin = std::chrono::steady_clock::now();
    for (auto& word : unsorted_words) {
        hash_table.add(word);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The insert time (hash): " << elapsed_ms.count() << " ms\n";

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i) {
        hash_table.search(unsorted_words[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The search 100000 values in (Hash): " << elapsed_ms.count() << " ms\n";
}

int main() {
    auto unsorted_words = load_dictionary_from_csv("dictionary.csv");

    use_AVL(unsorted_words);

    use_hasing(unsorted_words);
}
