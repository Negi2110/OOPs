// # ✅ **Static Arrays of Pointers to Objects — Explained**

// This concept is different from:

// * Static array of objects
// * Dynamic array of objects

// Here, we create an array that stores **pointers**, not objects themselves.

// ---

// ## ✔ **1. Declare a static array of pointers**

// ```cpp
// ClassName* arr[size];
// ```

// This creates an array of `size` **pointers**, but **no objects are created yet**.

// Diagram:

// ```
// arr → [nullptr][nullptr][nullptr][nullptr]...
// ```

// Initially, all pointers contain garbage or `nullptr` (if you set them).

// ---

// ## ✔ **2. Each element must be assigned a dynamically created object**

// Because the array holds pointers, you must allocate objects manually:

// ```cpp
// arr[i] = new ClassName();  
// ```

// Now `arr[i]` points to a real object on the heap.

// ```
// arr       → [*][*][*][*]
//              ↓   ↓
//             Obj Obj
// ```

// ---

// ## ✔ **3. Access member functions using `->`**

// Because elements are pointers:

// ```cpp
// arr[i]->function();
// ```

// NOT:

// ```cpp
// arr[i].function();   // ❌ Incorrect
// ```

// ---

// ## ✔ **4. Does NOT require a default constructor**

// This is the key difference from previous types.

// Since *you* explicitly choose how to construct each object:

// ```cpp
// arr[i] = new ClassName(10, 20);   // using a parameterized constructor
// ```

// There is **no need** for a default constructor.


#include <iostream>
using namespace std;

class Car {
public:
    Car(int id) {
        cout << "Car " << id << " created\n";
    }
    void drive() {
        cout << "Car driving\n";
    }
};

int main() {
    Car* cars[3];          // static array of pointers

    cars[0] = new Car(1);  // object created manually
    cars[1] = new Car(2);
    cars[2] = new Car(3);

    cars[0]->drive();
    cars[1]->drive();

    // cleanup
    for(int i = 0; i < 3; i++)
        delete cars[i];
}


        // ---

        // # 🔥 Interview-Level Summary

        // ### **Q: What does `ClassName* arr[size];` create?**

        // A static array of pointers to objects, NOT objects themselves.

        // ### **Q: When are objects created?**

        // Only when you write:

        // ```cpp
        // arr[i] = new ClassName();
        // ```

        // ### **Q: Do we need a default constructor?**

        // ❌ **No.**
        // Because you explicitly call any constructor you want.

        // ### **Q: How do we access member functions?**

        // Using:

        // ```cpp
        // arr[i]->member();
        // ```

        // ### **Q: Where are objects stored?**

        // On the **heap** (since `new` is used).

        // ---

        // If you want, I can also explain:

        // ✔ Static array of objects vs static array of pointers
        // ✔ Dynamic array of pointers
        // ✔ Which version is best for a defense simulation system (important for your project)
