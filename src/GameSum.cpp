#include "Game.h"

GameSum::GameSum(std::shared_ptr<Game> g1, std::shared_ptr<Game> g2) : game1(g1), game2(g2) {
}

std::vector<unsigned int> GameSum::get_valid_moves(bool player) const {
    std::vector<unsigned int> valid;
    for (const auto& m : game1->get_valid_moves(player)) {
        valid.push_back(m*2);
    }
    for (const auto& m : game2->get_valid_moves(player)) {
        valid.push_back(m*2 + 1);
    }
    return valid;
}

std::unique_ptr<Game> GameSum::make_move(int m, bool player) const {
    if (m%2 == 0) {
        return std::make_unique<GameSum>(game1->make_move(m/2, player), game2);
    } else {
        return std::make_unique<GameSum>(game1, game2->make_move(m/2, player));
    }
}

void GameSum::render() const {
    game1->render();
    game2->render();
}

Surreal GameSum::calculate_value() const {
    return (game1->get_value() + game2->get_value()).simplify();
}
