// ⭐ Interview Explanation (short)

// “When we pass objects as pointers, we pass their address instead of copying 
// the object. Inside the function we use the arrow operator (->) to access members.
//  This allows modifying the original object and avoids unnecessary copying.”
#include <iostream>
using namespace std;

class Player {
public:
    string name;
};

void Display(Player *p) {
    p->name = "Ravi"; // Modifying the original object's name
}

int main() {
    Player *myPlayer = new Player();
    myPlayer->name = "Aman";

    Display(myPlayer);

    cout << myPlayer->name << endl; // Displaying the modified name

    delete myPlayer;
    return 0;
}
    // “Anonymous objects are temporary objects created without storing them in a variable. They are useful when we need to pass an object directly to a function without keeping a reference.
    //  For example, Load(new Magazine(20)) creates a Magazine object on the heap and passes its pointer immediately. This avoids creating an extra variable.”