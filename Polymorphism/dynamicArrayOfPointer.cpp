// # ✅ **Dynamic Arrays of Pointers to Objects — Explained**

// This is the most flexible but also the most manual way of storing objects in arrays.

// It combines **dynamic memory allocation** + **pointer arrays**.

// ---

// # ✔ 1. The array name is a *pointer to a pointer*

// ```cpp
// ClassName** arr;
// ```
//
// Meaning:

// * `arr` points to the start of a **dynamic array of pointers**.
// * Each element is a pointer to an object.

// Diagram:

// ```
// arr → [*][*][*][*]...
// ```

// But none of these pointers point to real objects yet.

// ---

// # ✔ 2. Allocate the array of pointers dynamically

// ```cpp
// arr = new ClassName*[size];
// ```

// Now you have a dynamic array, but still no objects.

// ```
// arr       → [nullptr][nullptr][nullptr]...
// ```

// ---

// # ✔ 3. Create objects for each index

// Because each element is a pointer, you must allocate objects manually:

// ```cpp
// arr[i] = new ClassName(); 
// ```

// Now the structure becomes:

// ```
// arr       → [*][*][*]...
//              ↓  ↓  ↓
//             Obj Obj Obj
// ```

// Objects are stored in **heap memory**, and the pointer array itself is also on **heap**.

// ---

// # ✔ 4. Does NOT require a default constructor

// Why?

// Because you are explicitly creating each object with `new`, so you can use any constructor:

// ```cpp
// arr[i] = new ClassName(10, 20);   // parameterized constructor
// ```

// No default constructor is needed.

// ---

// # ✔ 5. Dereferencing

// Each element is a pointer, so you use:

// ```cpp
// arr[i]->function();
// ```

// And if you ever want the object itself:

// ```cpp
// *arr[i]
// ```

// ---

// # ⭐ Example Code (Interview Ready)


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
    int n = 3;

    Car** cars = new Car*[n];    // dynamic array of pointers

    for (int i = 0; i < n; i++) {
        cars[i] = new Car(i + 1);  // dynamic object creation
    }

    cars[0]->drive();
    cars[1]->drive();

    // cleanup
    for (int i = 0; i < n; i++)
        delete cars[i];

    delete[] cars;
}


// # 🔥 Interview-Level Summary

// ### ✔ What is `ClassName** arr`?

// A pointer to a pointer; used to store a dynamic array of pointers.

// ### ✔ What does `new ClassName*[size]` do?

// Creates a **dynamic array of pointers**, not objects.

// ### ✔ How do objects get created?

// Manually using:

// ```cpp
// arr[i] = new ClassName();
// ```

// ### ✔ Do we need a default constructor?

// ❌ **No**, because you explicitly call the constructor.

// ### ✔ How do we access functions?

// Using:

// ```cpp
// arr[i]->function();
// ```

// ### ✔ Where is memory stored?

// * The array of pointers → **heap**
// * Each object → **heap**

// ---
