#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include <map>

#include "Surreal.h"

class GameSum;

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

    GameSum* operator+(const Game* rhs) const;

    virtual std::vector<unsigned int> get_valid_moves(bool player) const = 0;
    virtual Game* make_move(int move, bool player = true) const = 0;
    virtual void render() const = 0;
protected:
    virtual Surreal calculate_value() const;
private:
    static std::map<const Game*, Surreal> value_table;
};

class GameSum : public Game {
public:
    GameSum(const Game* g1, const Game* g2);

    std::vector<unsigned int> get_valid_moves(bool player) const;
    Game* make_move(int move, bool player) const;
    void render() const;
protected:
    Surreal calculate_value() const;
private:
    const Game *game1, *game2;
    mutable unsigned int largest_move_in_game1;
};

#endif // GAME_H_INCLUDED
