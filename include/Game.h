#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>
#include <vector>
#include <map>

#include "Surreal.h"

class GameSum;
class Game;

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

    Surreal get_value(bool suicide = false) const;

    GameSum* operator+(const Game& rhs) const;
    GameSum* operator+(const Game* rhs) const;

    virtual std::vector<unsigned int> get_valid_moves(bool player) const = 0;
    virtual const Game* make_move(int m, bool player = true) const = 0;
    virtual void render() const = 0;

    virtual bool operator==(const Game* rhs) const = 0;
protected:
    virtual Surreal calculate_value() const;
private:
    //comparison based on logical state and not just memory address
    struct GameCompare {
        bool operator()(const Game* lhs, const Game* rhs) {
            return (lhs >= rhs) ? false : !(*lhs == rhs);
        }
    };
    static std::map<const Game*, Surreal, GameCompare> value_table;
};

GameSum* operator+(const Game* lhs, const Game& rhs);

class GameSum : public Game {
public:
    GameSum(const Game* g1, const Game* g2);
    ~GameSum();

    std::vector<unsigned int> get_valid_moves(bool player) const;
    const Game* make_move(int m, bool player) const;
    void render() const;

    virtual bool operator==(const Game* rhs) const;
protected:
    virtual Surreal calculate_value() const;
private:
    const Game *game1, *game2;
};

#endif // GAME_H_INCLUDED
