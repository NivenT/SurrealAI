#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>

#include "Surreal.h"

class Game {
public:
    Game();
    virtual ~Game();
    Surreal get_value() const;

    virtual std::vector<int> get_valid_moves() const = 0;
    virtual Game* make_move(int move) const = 0;
    virtual void render() = 0;
};

#endif // GAME_H_INCLUDED