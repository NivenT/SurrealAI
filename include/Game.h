#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>

#include "Surreal.h"

/**
Game class meant to represent specific types of games.
To be a Game it has to satisfy the following...
    * there are exactly 2 players
    * the players must alternate turns
    * there is complete information
    * it is deterministic
    * the first player unable to make a move loses
    * the game will always eventually end
*/
class Game {
public:
    Game() {}
    virtual ~Game() {}
    Surreal get_value() const;

    virtual std::vector<int> get_valid_moves(bool player) const = 0;
    virtual Game* make_move(int move) const = 0;
    virtual void render() const = 0;
};

#endif // GAME_H_INCLUDED
