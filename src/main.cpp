#include <iostream>

#include "Nim.h"

using namespace std;

int main() {
    Game* nim = new Nim(10);

    nim->render();
    nim = nim->make_move(3);
    nim->render();
    nim = nim->make_move(2);
    nim->render();
    nim = nim->make_move(1);
    nim->render();
    nim = nim->make_move(3);
    nim->render();
    nim = nim->make_move(1);
    nim->render();

    return 0;
}
