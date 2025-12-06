#include <iostream>
using namespace std;

class Player {
public:
    // Static data member shared by ALL Player objects
    static int instances;//static data members are not initialised inside the constructor

    // Constructor increments the static counter
    Player() {
        instances++;  
        cout << "Player created. Total = " << instances << endl;
    }
};

// Definition (and optional initialization) of the static member
// Required in C++! Storage allocated here.
int Player::instances = 0;

int main() {

    Player p1;   // instances = 1
    
    Player p2;   // instances = 2
    
    Player p3;   // instances = 3

    // Access static member without object
    cout << "Final instance count = " << Player::instances << endl;
   

    return 0;
}
