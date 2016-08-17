#include "Game.h"

std::map<const Game*, Surreal> Game::value_table;

Surreal Game::get_value() const {
    if (value_table.find(this) == value_table.end()) {
        value_table[this] = calculate_value();
    }
    return value_table[this];
}

Surreal Game::calculate_value() const {
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

GameSum* Game::operator+(const Game* rhs) const {
    return new GameSum(this, rhs);
}
