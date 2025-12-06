#include <iostream>
using namespace std;

class Player {
public:

    // Static data member (shared by ALL Player objects)
    static int instances;

    // Constructor
    Player() {
        instances++;   // Increment the shared static counter
    }

    // Static member function
    // ✔ Can access ONLY static members
    // ✔ Does NOT have a 'this' pointer
    // ✔ Can be called using object OR class name
    static void PrintStaticValues() {
        cout << "Instances = " << instances << endl;
    }
};

// Definition + initialization of static member
int Player::instances = 0;

int main() {

    // Create a Player object dynamically
    Player *player1 = new Player();   // instances = 1

    // Calling static member function using object pointer
    player1->PrintStaticValues();     // Output: 1

    // Calling static member function using class name (recommended)
    Player::PrintStaticValues();      // Output: 1

    return 0;
}
