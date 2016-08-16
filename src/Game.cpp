#include "Game.h"

Surreal Game::get_value() const {
    Surreal::Set left, right;
    for (const auto& move : get_valid_moves(true)) {
        Game* temp = make_move(move);
        left.insert(temp->get_value());
        delete temp;
    }
    for (const auto& move : get_valid_moves(false)) {
        Game* temp = make_move(move);
        right.insert(temp->get_value());
        delete temp;
    }
    return Surreal(left, right);
}
