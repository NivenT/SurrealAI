#include "Game.h"

using namespace std;

GameSum::GameSum(const Game* g1, const Game* g2) : game1(g1), game2(g2) {
}

vector<unsigned int> GameSum::get_valid_moves(bool player) const {
    vector<unsigned int> valid;
    for (const auto& m : game1->get_valid_moves(player)) {
        valid.push_back(m*2);
    }
    for (const auto& m : game2->get_valid_moves(player)) {
        valid.push_back(m*2 + 1);
    }
    return valid;
}

const Game* GameSum::make_move(int m, bool player) const {
    if (m%2 == 0) {
        return new GameSum(game1->make_move(m/2, player), game2);
    } else {
        return new GameSum(game1, game2->make_move(m/2, player));
    }
}

void GameSum::render() const {
    game1->render();
    game2->render();
}

Surreal GameSum::calculate_value() const {
    return game1->get_value() + game2->get_value();
}

bool GameSum::operator==(const Game* rhs) const {
    const GameSum* rhs_sum = dynamic_cast<const GameSum*>(rhs);
    if (rhs_sum) {
        return !(*game1 == rhs_sum->game1) ? false : (*game2 == rhs_sum->game2);
    } else {
        return false;
    }
}
