#include "Nim.h"

Nim::Nim(int heap) : heap_size(heap) {
    possible_moves = {1, 2, 3};
}

Nim::Nim(int heap, std::vector<int> poss) : heap_size(heap), possible_moves(poss) {
}

std::vector<int> Nim::get_valid_moves(bool player) const {
    std::vector<int> poss = possible_moves;
    for (int i = 0; i < poss.size(); i++) {
        if (poss[i] > heap_size) {
            poss[i--] = poss.back();
            poss.pop_back();
        }
    }
    return poss;
}

Game* Nim::make_move(int move) const {
    return new Nim(heap_size-move, possible_moves);
}

void Nim::render() const {
    std::cout<<heap_size<<": ";
    for (int i = 0; i < heap_size; i++) {
        std::cout<<"*";
    }
    std::cout<<std::endl;
}
