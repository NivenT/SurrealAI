#include <algorithm>

#include "Nim.h"

using namespace std;

bool play_nim() {
    Game* nim = new Nim(67, {4, 11, 3, 6, 13});

    nim->render();
    bool turn = rand()%2; //HUMAN is left player (true)

    while (true) {
        vector<unsigned int> poss = nim->get_valid_moves(turn); int m = 0;
        if (poss.empty()) {
            break;
        } else if (turn) {
            cout<<"How many stars would you like to remove? ";
            cin>>m;

            while (std::find(poss.begin(), poss.end(), m) == poss.end()) {
                cout<<"That's not a valid number of stars. How many would you like to remove? ";
                cin>>m;
            }
        } else {
            m = poss[0];
            for (int i = 0; i < poss.size(); i++) {
                Surreal value = nim->make_move(poss[i])->get_value();
                if (value <= 0) {
                    m = poss[i];
                    break;
                }
            }

            cout<<"I will remove "<<m<<" stars"<<endl;
        }

        poss.clear();
        Game* temp = nim->make_move(m); delete nim;
        nim = temp;

        turn = !turn;
        nim->render();
        cout<<endl;
    }
    return !turn;
}

bool play_2heap_nim() {
    Nim g1(13);
    Game* nim2 = g1 + new Nim(17);

    nim2->render();
    bool turn = rand()%2;

    while (true) {
        vector<unsigned int> poss = nim2->get_valid_moves(turn); int m = 0;
        if (poss.empty()) {
            break;
        } else if (turn) {
            int heap = 0;
            do {
                cout<<"Which heap would you like to remove stars from (0/1)? ";
                cin>>heap;

                while (heap < 0 || heap > 1) {
                    cout<<"That's not a valid heap. Which heap do you choose? ";
                    cin>>heap;
                }

                cout<<"How many stars would you like to remove from heap "<<heap<<"? ";
                cin>>m;
                m = m*2 + heap;
            } while (std::find(poss.begin(), poss.end(), m) == poss.end());
        } else {
            m = poss[0];
            for (int i = 0; i < poss.size(); i++) {
                Surreal value = nim2->make_move(poss[i])->get_value();
                if (value <= 0) {
                    m = poss[i];
                    break;
                }
            }

            cout<<"I will remove "<<(m/2)<<" stars from heap "<<(m%2)<<endl;
        }

        poss.clear();
        Game* temp = nim2->make_move(m); delete nim2;
        nim2 = temp;

        turn = !turn;
        nim2->render();
        cout<<endl;
    }
}

int main() {
    srand(time(nullptr));
    bool winner = play_2heap_nim();

    cout<<"The winner is "<<(winner ? "HUMAN" : "COMPUTER")<<endl;

    return 0;
}
