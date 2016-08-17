#include "Game.h"

std::map<const Game*, Surreal, Game::GameCompare> Game::value_table;

Surreal Game::get_value() const {
    if (value_table.find(this) == value_table.end()) {
        value_table[this] = calculate_value();
    }
    return value_table[this];
}

Surreal Game::calculate_value() const {
    Surreal::Set left, right;
    for (const auto& m : get_valid_moves(true)) {
        left.insert(make_move(m)->get_value());
    }
    for (const auto& m : get_valid_moves(false)) {
        right.insert(make_move(m)->get_value());
    }
    return Surreal(left, right);
}

GameSum* Game::operator+(const Game& rhs) const {
    return new GameSum(this, &rhs);
}


GameSum* Game::operator+(const Game* rhs) const {
    return new GameSum(this, rhs);
}

GameSum* operator+(const Game* lhs, const Game& rhs) {
    return new GameSum(lhs, &rhs);
}
