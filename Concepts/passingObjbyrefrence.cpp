// What is happening? (Simple explanation)
// ✔ Player*& p

// means:

// p is not a new pointer

// p is an alias of myPlayer

// Any change through p affects myPlayer

// ✔ Modifying the object?

// Yes, both p and myPlayer point to the same object.

// ✔ Modifying the pointer itself?

// You can — because it’s passed by reference.

// ⭐ Interview-Friendly Summary

// Use this in interviews:

// “When we pass a pointer normally, the pointer is passed by value, so we can modify the object but not the pointer itself.

// If we want to modify the pointer (make it point somewhere else), we pass it by reference using Type*&.

// Player*& p means the function receives the real pointer, not a copy.”
#include <iostream>
using namespace std;

class Player {
public:
    string name;
};

void Display(Player *&p) {   // Passing pointer by reference
    p->name = "Ravi";         // Modifying original object
}

int main() {
    Player *myPlayer = new Player();
    myPlayer->name = "Aman";

    Display(myPlayer);

    cout << myPlayer->name << endl; // Output: Ravi

    delete myPlayer;
    return 0;
}
