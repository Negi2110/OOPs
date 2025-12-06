// # ✅ **Static Data Members – Interview Notes**

// ### ✔ Static member = one shared variable for the entire class

// * Only **one copy** exists in memory, no matter how many objects you create.
// * All objects share this value.

// ---

// # 🧠 Key Rule: **Declare inside the class, but DEFINE outside**

// ### Inside the class:

// ```cpp
// static int instances;      // declaration ONLY
// ```

// ### Outside the class:

// ```cpp
// int Player::instances = 0; // definition + initialization
// ```

// Why?

// ### ✔ Because static members need one single memory location

// The class declaration **does NOT allocate memory** for static members.
// Memory is allocated **only when defined outside** the class.

// ---

// # ⚠️ Why NOT put the static definition in a header file?

// If you place:

// ```cpp
// int Player::instances = 0;
// ```

// inside a `.h` file, every `.cpp` file that includes the header will generate **a duplicate definition**, causing:

// ```
// multiple definition of Player::instances
// ld: error: duplicate symbol
// ```

// Therefore:

// ### ✔ Put static definitions only in a `.cpp` file

// ### ❌ Do NOT put them inside headers

// ---

// # ✅ **Correct Code (Matching Your Slide)**

#include <iostream>
using namespace std;

class Player {
public:
    static int instances;   // Declaration of static member

    Player() {
        instances++;        // Increment shared counter
    }
};

// Definition + initialization (must be outside class)
int Player::instances = 0;

int main() {
    Player p1;
    Player p2;
    Player p3;

    cout << "Number of Player instances: " << Player::instances << endl;
    return 0;
}
// ```

// ---

// # ✔ Expected Output:

// ```
// Number of Player instances: 3
// ```

// ---

// # 📌 **Copy-Paste Interview Summary**

// * Static data members belong to the **class**, not individual objects.
// * They are **declared inside the class** but **defined outside it**.
// * Static variables must be defined in a `.cpp` file to avoid **multiple definition errors**.
// * All objects share the same static member.

// ---

