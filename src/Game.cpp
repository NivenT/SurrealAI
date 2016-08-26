#include "Game.h"

Surreal Game::get_value() const {
    return is_memoizable() ? std::move(get_memo_value()) : std::move(calculate_value());
}

Surreal Game::calculate_value() const {
    Surreal::Set left, right;
    for (const auto& m : get_valid_moves(true)) {
        left.insert(std::move(make_move(m)->get_value()));
    }
    for (const auto& m : get_valid_moves(false)) {
        right.insert(std::move(make_move(m)->get_value()));
    }
    return Surreal(std::move(left), std::move(right)).simplify();
}

Surreal Game::get_memo_value() const {
    return calculate_value();
}

bool Game::is_memoizable() const {
    return false;
}
