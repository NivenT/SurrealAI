#include <iostream>
#include <algorithm>

#include "Nim.h"

using namespace std;

int main() {
    srand(time(nullptr));
    Game* nim = new Nim(13);

    cout<<"2* = "<<(star+star).pretty()<<endl;

    Surreal val = nim->get_value();

    cout<<"val: "<<val.pretty()<<endl;
    cout<<"val.sign(): "<<val.sign()<<endl;
    cout<<"val.left.size(): "<<val.left.size()<<endl;
    cout<<"val.right.size(): "<<val.right.size()<<endl;

    std::vector<int> poss = nim->get_valid_moves(false);
    for (auto& move : poss) {
        cout<<nim->make_move(move)->get_value().pretty()<<endl;
    }

    cout<<star.pretty()<<endl;
    cout<<(star == 0)<<endl;

    Surreal::Set left, right;
    left.insert(star);
    left.insert(0);
    right.insert(star);
    right.insert(0);

    cout<<"{L | R} = "<<Surreal(left, right)<<endl
        <<"{L | R} = "<<Surreal(left, right).pretty()<<endl;

    return 0;
    nim->render();
    bool turn = rand()%2; //HUMAN is left player (true)

    bool game_over = false;
    while (!game_over) {
        std::vector<int> poss = nim->get_valid_moves(turn);
        if (poss.empty()) {
            break;
        } else if (turn) {
            int move = 0;
            cout<<"How many stars would you like to remove? ";
            cin>>move;

            while (std::find(poss.begin(), poss.end(), move) == poss.end()) {
                cout<<"That's not a valid number of stars. How many would you like to remove? ";
                cin>>move;
            }

            nim = nim->make_move(move);
        } else {
            int move = poss[0];
            for (int i = 0; i < poss.size(); i++) {
                Surreal value = nim->make_move(poss[i])->get_value();
                if (value <= 0) {
                    move = poss[i];
                    break;
                }
            }
            /*
            cout<<"values: "<<endl
                <<nim->make_move(poss[0])->get_value().pretty()<<endl
                <<nim->make_move(poss[1])->get_value().pretty()<<endl
                <<nim->make_move(poss[2])->get_value().pretty()<<endl
                <<endl;
            /**/
            cout<<"signs of values: "<<endl
                <<nim->make_move(poss[0])->get_value().sign()<<endl
                <<nim->make_move(poss[1])->get_value().sign()<<endl
                <<nim->make_move(poss[2])->get_value().sign()<<endl
                <<endl;
            /**/
            cout<<"I will remove "<<move<<" stars"<<endl;
            nim = nim->make_move(move);
        }
        turn = !turn;
        nim->render();
    }
    cout<<"The winner is "<<(turn ? "COMPUTER" : "HUMAN")<<endl;

    return 0;
}
