#include <iostream>

#include "Surreal.h"

using namespace std;

int main() {
    for (int a = -1; a < 2; a++) {
        for (int b = -1; b < 2; b++) {
            Surreal surA(a), surB(b);
            cout<<a<<" <= "<<b<<" -> "<<(surA<=surB)<<endl
                <<a<<" < "<<b<<"  -> "<<(surA< surB)<<endl
                <<a<<" >= "<<b<<" -> "<<(surA>=surB)<<endl
                <<a<<" > "<<b<<"  -> "<<(surA> surB)<<endl
                <<a<<" == "<<b<<" -> "<<(surA==surB)<<endl
                <<a<<" != "<<b<<" -> "<<(surA!=surB)<<endl
                <<endl;
        }
    }
    cout<<(Surreal(-1,1)==Surreal())<<endl
        <<(Surreal(0) == Surreal())<<endl
        <<endl;

    cout<<"0 = "<<Surreal(0)<<endl
        <<"1 = "<<Surreal(1).pretty()<<endl
        <<"1 = "<<Surreal(1)<<endl
        <<"1 = "<<Surreal(1).pretty()<<endl
        <<"2 = "<<Surreal(2).pretty()<<endl
        <<"2 = "<<Surreal(2)<<endl
        <<"1/2 = "<<Surreal(0,1)<<endl
        <<"1/2 = "<<Surreal(0,1).pretty()<<endl
        <<"1 = "<<Surreal(Surreal(0,1),Surreal(1,2))<<endl
        <<"1 = "<<Surreal(Surreal(0,1),Surreal(1,2)).pretty()<<endl
        <<endl;

    cout<<"1 + 1  = "<<Surreal(1)+Surreal(1)<<endl
        <<"-1 + 1 = "<<(Surreal(-1)+Surreal(1)).pretty()<<endl
        <<endl;
    return 0;
}
