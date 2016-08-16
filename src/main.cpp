#include <iostream>
#include <algorithm>

#include "Nim.h"

using namespace std;

int main() {
    srand(time(nullptr));
    Game* nim = new Nim(12);

    nim->render();
    bool turn = rand()%2; //HUMAN is left player (true)

    bool game_over = false;
    while (!game_over) {
        std::vector<int> poss = nim->get_valid_moves(turn);
        int move = 0;
        if (poss.empty()) {
            break;
        } else if (turn) {
            cout<<"How many stars would you like to remove? ";
            cin>>move;

            while (std::find(poss.begin(), poss.end(), move) == poss.end()) {
                cout<<"That's not a valid number of stars. How many would you like to remove? ";
                cin>>move;
            }
        } else {
            move = poss[0];
            for (int i = 0; i < poss.size(); i++) {
                Surreal value = nim->make_move(poss[i])->get_value();
                if (value <= 0) {
                    move = poss[i];
                    break;
                }
            }
            /**
            cout<<"values: "<<endl
                <<nim->make_move(poss[0])->get_value().pretty()<<endl
                <<nim->make_move(poss[1])->get_value().pretty()<<endl
                <<nim->make_move(poss[2])->get_value().pretty()<<endl
                <<endl;
            /**
            cout<<"signs of values: "<<endl
                <<nim->make_move(poss[0])->get_value().sign()<<endl
                <<nim->make_move(poss[1])->get_value().sign()<<endl
                <<nim->make_move(poss[2])->get_value().sign()<<endl
                <<endl;
            /**/
            cout<<"I will remove "<<move<<" stars"<<endl;
        }

        poss.clear();
        Game* temp = nim->make_move(move);
        delete nim;
        nim = temp;

        turn = !turn;
        nim->render();
    }
    cout<<"The winner is "<<(turn ? "COMPUTER" : "HUMAN")<<endl;

    return 0;
}
