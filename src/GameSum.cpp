#include <algorithm>

#include "Game.h"

GameSum::GameSum(const Game* g1, const Game* g2) : game1(g1), game2(g2), largest_move_in_game1(0) {
}

std::vector<unsigned int> GameSum::get_valid_moves(bool player) const {
    auto valid = game1->get_valid_moves(player);
    largest_move_in_game1 = *std::max_element(valid.begin(), valid.end()); //Is this really safe?
    for (const auto& m : game2->get_valid_moves(player)) {
        valid.push_back(m + largest_move_in_game1 + 1);
    }
    return valid;
}

Game* GameSum::make_move(int move, bool player) const {
    if (largest_move_in_game1 == 0) {
        largest_move_in_game1 = game1->get_valid_moves(player).size();
    }
    if (move <= largest_move_in_game1) {
        return new GameSum(game1->make_move(move, player), game2);
    } else {
        return new GameSum(game1, game2->make_move(move-largest_move_in_game1-1, player));
    }
}

void GameSum::render() const {
    game1->render();
    game2->render();
}

Surreal GameSum::calculate_value() const {
    return game1->get_value() + game2->get_value();
}
