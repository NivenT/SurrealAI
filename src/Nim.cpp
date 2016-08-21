#include "Nim.h"

using namespace std;

Nim::Nim(int heap) : heap_size(heap) {
    possible_moves = {3, 2, 1};
}

Nim::Nim(int heap, vector<unsigned int> poss) : possible_moves(poss), heap_size(heap) {
}

Nim::~Nim() {
    possible_moves.clear();
}

vector<unsigned int> Nim::get_valid_moves(bool player) const {
    vector<unsigned int> poss = possible_moves;
    for (int i = 0; i < poss.size(); i++) {
        if (poss[i] > heap_size) {
            poss[i--] = poss.back();
            poss.pop_back();
        }
    }
    return poss;
}

const Game* Nim::make_move(int m, bool player) const {
    return new Nim(heap_size-m, possible_moves);
}

void Nim::render() const {
    cout<<heap_size<<": ";
    for (int i = 0; i < heap_size; i++) {
        cout<<"*";
    }
    cout<<endl;
}

bool Nim::operator==(const Game* rhs) const {
    int rhs_heap_size = ((Nim*)rhs)->heap_size;
    return (heap_size != rhs_heap_size) ? false : equal(possible_moves.begin(), possible_moves.end(), ((Nim*)rhs)->possible_moves.begin());
}
