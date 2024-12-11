#include "word.h"

ostream& operator<<(ostream& ost, const Word& word) {
    ost << word.name << " - " << word.description;
    return ost;
}
