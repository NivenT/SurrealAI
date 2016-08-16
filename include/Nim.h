#ifndef NIM_H_INCLUDED
#define NIM_H_INCLUDED

#include "Game.h"

class Nim : public Game {
public:
    Nim(int heap);
    Nim(int heap, std::vector<int> poss);
    ~Nim();

    std::vector<int> get_valid_moves(bool player) const;
    Game* make_move(int move) const;
    void render() const;
private:
    std::vector<int> possible_moves;
    int heap_size;
};

#endif // NIM_H_INCLUDED
