// # ✅ **Static Member Functions – Interview Notes**

// ### ✔ What is a static member function?

// A member function declared with the keyword `static`.

// Example:

// ```cpp
// static void showCount();
// ```

// ---

// # 🧠 **Key Properties of Static Member Functions**

// ### 1️⃣ **Can access ONLY static data members**

// Because static functions do not belong to an object — they belong to the class.

// So this is **NOT allowed**:

// ```cpp
// cout << nonStaticVar;   // ❌ ERROR
// ```

// But this is allowed:

// ```cpp
// cout << staticVar;      // ✔ OK
// ```

// ---

// ### 2️⃣ **Does NOT have a `this` pointer**

// Normal member functions internally receive:

// ```
// this → pointer to the calling object
// ```

// Static functions **do not receive** a `this` pointer because they do not operate on any specific object.

// ---

// ### 3️⃣ **Can be called without creating an object**

// ```cpp
// ClassName::functionName();
// ```

// ---

// ### 4️⃣ **Defined outside the class WITHOUT the static keyword**

// Inside the class (declaration):

// ```cpp
// static void display();
// ```

// Outside the class (definition):

// ```cpp
// void ClassName::display() { }
// ```

// ---

// # ✅ **Code Example (Fully Commented)**

// ```cpp
#include <iostream>
using namespace std;

class Player {
public:
    static int count;      // Static data member

    Player() {
        count++;           // Modify static member
    }

    // Static member function
    static void showCount() {
        // cout << name;   ❌ ERROR: cannot access non-static members
        cout << "Player count = " << count << endl;
    }
};

// Define static data member outside the class
int Player::count = 0;

int main() {

    Player p1;
    Player p2;

    // Call static function using class name
    Player::showCount();   // Output: Player count = 2

    // Can also call through an object (not preferred)
    p1.showCount();        // Output: Player count = 2

    return 0;
}
// ```

// ---

// # 📌 **Why static function cannot access non-static members?**

// Because non-static members belong to **objects**, and static functions do **not know which object** to access (no `this` pointer).

// ---

// # 📌 **Copy-Paste Interview Summary**

// * Static member functions belong to the **class**, not objects.
// * They can only access **static data members**.
// * They have **no `this` pointer**.
// * Declared with `static` keyword inside class.
// * When defined outside the class, **do NOT write `static` again**.
// * Can be called using `ClassName::functionName()` without an object.


// “The copy constructor is invoked for the object being created, not for the source object.
// In MyClass obj2 = *obj1;, obj2 is being constructed, so obj2 triggers the copy constructor.”