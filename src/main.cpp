#include <algorithm>

#include "Nim.h"

using namespace std;

bool play_nim() {
    vector<unsigned int> moves{4, 11, 3, 6, 13};
    unique_ptr<Game> nim = make_unique<Nim>(40, moves);

    bool turn = rand()%2; //HUMAN is left player (true)
    nim->render();
    cout<<endl;

    while (true) {
        vector<unsigned int> poss = nim->get_valid_moves(turn); int m = 0;
        if (poss.empty()) {
            break;
        } else if (turn) {
            cout<<"How many stars would you like to remove? ";
            cin>>m;

            while (find(poss.begin(), poss.end(), m) == poss.end()) {
                cout<<"That's not a valid number of stars. How many would you like to remove? ";
                cin>>m;
            }
        } else {
            m = poss[0];
            for (size_t i = 0; i < poss.size(); i++) {
                Surreal value = nim->make_move(poss[i])->get_value();
                if (value <= 0) {
                    m = poss[i];
                    break;
                }
            }

            cout<<"I will remove "<<m<<" stars"<<endl;
        }

        poss.clear();
        nim = nim->make_move(m);

        turn = !turn;
        nim->render();
        cout<<endl;
    }
    return !turn;
}

bool play_2heap_nim() {
    unique_ptr<Game> nim2 = make_unique<GameSum>(make_shared<Nim>(6), make_shared<Nim>(4));

    bool turn = rand()%2; //HUMAN is left player (true)
    nim2->render();
    cout<<endl;

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
            } while (find(poss.begin(), poss.end(), m) == poss.end());
        } else {
            m = poss[0];
            for (size_t i = 0; i < poss.size(); i++) {
                Surreal value = nim2->make_move(poss[i])->get_value();
                if (value <= 0) {
                    m = poss[i];
                    break;
                }
            }

            cout<<"I will remove "<<(m/2)<<" "<<(m/2 == 1 ? "star" : "stars")<<" from heap "<<(m%2)<<endl;
        }

        poss.clear();
        nim2 = nim2->make_move(m);

        turn = !turn;
        nim2->render();
        cout<<endl;
    }
    return !turn;
}

int main() {
    /** Tests
    cout<<Surreal({0,1,2,3,4,5},{Surreal::Star(4), star}).simplify().pretty()<<endl
        <<Surreal({0,star, star, star, star, star,0,0},{0, 0, star}).simplify().pretty()<<endl
        <<Surreal({star, 2},{-1, -3, 4, star}).simplify().pretty()<<endl
        <<Surreal({0,1},{1, -1, 0}).simplify().pretty()<<endl
        <<Surreal({star, Surreal::Star(2)},{1, 0, Surreal::Star(5)}).simplify().pretty()<<endl
        <<(Surreal(5) + Surreal(7)).pretty()<<endl
        <<(Surreal::Star(3) + Surreal::Star(5)).simplify().pretty()<<endl
        <<((Surreal::Star(3) + Surreal::Star(5)) == Surreal::Star(6))<<endl
        <<(Surreal::Star(4) + 1).simplify().pretty()<<endl
        <<endl;
    return 0;
    **/

    srand(time(nullptr));
    bool winner = play_2heap_nim();

    cout<<"The winner is "<<(winner ? "HUMAN" : "COMPUTER")<<endl;

    return 0;
}
