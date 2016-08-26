#include "Game.h"

using namespace std;

Surreal Game::get_value() const {
    return calculate_value();
}

Surreal Game::calculate_value() const {
    Surreal::Set left, right;
    for (const auto& m : get_valid_moves(true)) {
        const Game* temp = make_move(m);
        left.insert(move(temp->calculate_value()));
        delete temp;
    }
    for (const auto& m : get_valid_moves(false)) {
        const Game* temp = make_move(m);
        right.insert(move(temp->calculate_value()));
        delete temp;
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
