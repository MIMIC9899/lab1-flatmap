#pragma once
#include "pair.h"

class Iterator {
private:
    Pair* current;
public:
    Iterator(Pair* ptr) : current(ptr) {}

    Pair& operator*() {
        return *current;
    }

    Iterator& operator++() {
        ++current;
        return *this;
    }

    Iterator& operator--() {
        --current;
        return *this;
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};
