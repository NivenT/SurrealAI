#include "Game.h"

using namespace std;

map<const Game*, Surreal, Game::GameCompare> Game::value_table;

Surreal Game::get_value(bool suicide) const {
    auto it = value_table.find(this);
    if (it == value_table.end()) {
        value_table[this] = move(calculate_value());
    } else if (it->first != this && suicide) {
        Surreal value = move(value_table[this]);
        delete this;
        return value;
    }
    return value_table[this];
}

Surreal Game::calculate_value() const {
    Surreal::Set left, right;
    for (const auto& m : get_valid_moves(true)) {
        left.insert(move(make_move(m)->get_value(true)));
    }
    for (const auto& m : get_valid_moves(false)) {
        right.insert(move(make_move(m)->get_value(true)));
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
