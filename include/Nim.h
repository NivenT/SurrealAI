#ifndef NIM_H_INCLUDED
#define NIM_H_INCLUDED

#include "Game.h"

class Nim : public Game {
public:
    Nim(int heap);
    Nim(int heap, std::vector<unsigned int> poss);
    ~Nim();

    std::vector<unsigned int> get_valid_moves(bool player) const;
    Game* make_move(int m, bool player) const;
    void render() const;

    bool operator==(const Game* rhs) const;
private:
    std::vector<unsigned int> possible_moves;
    int heap_size;
};

#endif // NIM_H_INCLUDED
