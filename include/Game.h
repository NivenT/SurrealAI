#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>
#include <vector>

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

    Surreal get_value() const;

    virtual std::vector<unsigned int> get_valid_moves(bool player) const = 0;
    virtual std::unique_ptr<Game> make_move(int m, bool player = true) const = 0;
    virtual void render() const = 0;
protected:
    virtual Surreal calculate_value() const;
    virtual Surreal get_memo_value() const;
    virtual bool is_memoizable() const;
};

class GameSum : public Game {
public:
    GameSum(std::shared_ptr<Game> g1, std::shared_ptr<Game> g2);

    std::vector<unsigned int> get_valid_moves(bool player) const override;
    std::unique_ptr<Game> make_move(int m, bool player) const override;
    void render() const override;
protected:
    Surreal calculate_value() const override;
private:
    std::shared_ptr<Game> game1, game2;
};

#endif // GAME_H_INCLUDED
