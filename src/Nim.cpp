#include <iostream>

#include "Nim.h"

struct NimCompare {
    bool operator()(const Nim& lhs, const Nim& rhs) {
        return (lhs.heap_size < rhs.heap_size) ? true : !std::equal(lhs.possible_moves.begin(), lhs.possible_moves.end(), rhs.possible_moves.begin());
    }
};

std::map<Nim, Surreal, NimCompare> Nim::value_table;

Nim::Nim(unsigned int heap) : possible_moves{3, 2, 1}, heap_size(heap) {
}

Nim::Nim(unsigned int heap, std::vector<unsigned int> poss) : possible_moves(poss), heap_size(heap) {
}

Nim::~Nim() {
    possible_moves.clear();
}

std::vector<unsigned int> Nim::get_valid_moves(bool) const {
    std::vector<unsigned int> poss = possible_moves;
    for (size_t i = 0; i < poss.size(); i++) {
        if (poss[i] > heap_size) {
            poss[i--] = poss.back();
            poss.pop_back();
        }
    }
    return poss;
}

Surreal Nim::get_memo_value() const {
    if (value_table.find(*this) == value_table.end()) {
        return value_table[*this] = calculate_value();
    }
    return value_table[*this];
}

bool Nim::is_memoizable() const {
    return true;
}

std::unique_ptr<Game> Nim::make_move(int m, bool) const {
    return std::make_unique<Nim>(heap_size-m, possible_moves);
}

void Nim::render() const {
    std::cout<<heap_size<<": ";
    for (size_t i = 0; i < heap_size; i++) {
        std::cout<<"*";
    }
    std::cout<<std::endl;
}
