#include <algorithm>
#include <iostream>

#include "Nim.h"
#include "Notakto.h"

using namespace std;

bool play_simple_game(unique_ptr<Game> game, const string& prompt, const string& ai_response, const string& invalid_prompt = "That's not a valid move. Which move would you like to make? ") {
    bool turn = rand()%2; //true means players turn
    game->render();
    cout<<endl;

    while (true) {
        vector<unsigned int> poss = game->get_valid_moves(turn); int m = 0;
        if (poss.empty()) {
            break;
        } else if (turn) {
            cout<<prompt;
            cin>>m;

            while (find(poss.begin(), poss.end(), m) == poss.end()) {
                cout<<invalid_prompt;
                cin>>m;
            }
        } else {
            m = poss[0];
            for (size_t i = 0; i < poss.size(); i++) {
                Surreal value = game->make_move(poss[i])->get_value();
                if (value <= 0) {
                    m = poss[i];
                    break;
                }
            }

            printf(ai_response.c_str(), m);
            cout<<endl;
        }

        poss.clear();
        game = game->make_move(m);

        turn = !turn;
        game->render();
        cout<<endl;
    }
    return !turn;
}

bool play_sum_game(unique_ptr<Game> game, const string& prompt0, const string& prompt1, const string& ai_response0, const string& ai_response1) {
    bool turn = rand()%2; //HUMAN is left player (true)
    game->render();
    cout<<endl;

    while (true) {
        vector<unsigned int> poss = game->get_valid_moves(turn); int m = 0;
        if (poss.empty()) {
            break;
        } else if (turn) {
            int g = 0;
            do {
                cout<<"Which game would you like to make a move in (0/1)? ";
                cin>>g;

                while (g < 0 || g > 1) {
                    cout<<"That's not a valid game. Which one do you choose? ";
                    cin>>g;
                }

                cout<<(g ? prompt1 : prompt0);
                cin>>m;
                m = m*2 + g;
            } while (find(poss.begin(), poss.end(), m) == poss.end());
        } else {
            m = poss[0];
            for (size_t i = 0; i < poss.size(); i++) {
                Surreal value = game->make_move(poss[i], false)->get_value();
                if (value <= 0) {
                    m = poss[i];
                    break;
                }
            }

            cout<<"I will make a move in game "<<m%2<<endl;
            printf(m%2 ? ai_response1.c_str() : ai_response0.c_str(), m/2);
            cout<<endl;
        }

        poss.clear();
        game = game->make_move(m, turn);

        turn = !turn;
        game->render();
        cout<<endl;
    }
    return !turn;
}

int main() {
    srand(time(nullptr));
    /** //2 heap nim
    bool winner = play_sum_game(make_unique<GameSum>(make_shared<Nim>(6), make_shared<Nim>(4)),
                                "How many stars will you remove? ",
                                "How many stars will you remove? ",
                                "I will remove %d star(s).",
                                "I will remove %d star(s).");
    /** //2 board noktakto
    bool winner = play_sum_game(make_unique<GameSum>(make_shared<Notakto>(), make_shared<Notakto>()),
                                "Where will you move? ",
                                "Where will you move? ",
                                "I will move at position %d.",
                                "I will move at position %d.");
    /**/ //notakto + nim
    bool winner = play_sum_game(make_unique<GameSum>(make_shared<Notakto>(), make_shared<Nim>(4)),
                                "Where will you move? ",
                                "How many stars will you remove? ",
                                "I will move at position %d.",
                                "I will remove %d star(s).");
    /** //nim
    vector<unsigned int> moves{4, 11, 3, 6, 13};
    bool winner = play_simple_game(make_unique<Nim>(40, moves),
                                   "How many stars would you like to remove? ",
                                   "I will remove %d star(s).");
    /** //X's only tic-tac-toe
    bool winner = play_simple_game(make_unique<Notakto>(),
                                   "Where will you move? ",
                                   "I will move at position %d.");
    /**/

    cout<<"The winner is "<<(winner ? "HUMAN" : "COMPUTER")<<endl;

    return 0;
}
