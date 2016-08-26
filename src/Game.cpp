#include "Game.h"

Surreal Game::get_value() const {
    return calculate_value();
}

Surreal Game::calculate_value() const {
    Surreal::Set left, right;
    for (const auto& m : get_valid_moves(true)) {
        left.insert(std::move(make_move(m)->calculate_value()));
    }
    for (const auto& m : get_valid_moves(false)) {
        right.insert(std::move(make_move(m)->calculate_value()));
    }
    return Surreal(left, right);
}
