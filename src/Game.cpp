#include "Game.h"

Surreal Game::get_value() const {
    Surreal::Set left, right;
    for (const auto& move : get_valid_moves(true)) {
        left.insert(make_move(move)->get_value());
    }
    for (const auto& move : get_valid_moves(false)) {
        right.insert(make_move(move)->get_value());
    }
    return Surreal(left, right);
}
