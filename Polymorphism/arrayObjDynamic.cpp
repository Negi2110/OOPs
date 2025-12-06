
// # ✅ **Dynamic Sized Arrays of Objects — Explained**

// Dynamic arrays allow you to create an array **whose size is known only at runtime**.
// These arrays are created in **heap memory** using `new`.

// ---

// ## ✔ **1. Declare a pointer**

// ```cpp
// type* identifier;
// ```

// This does *not* create objects — it just creates a pointer that will later point to a dynamic array.

// ---

// ## ✔ **2. Allocate the array using `new`**

// ```cpp
// identifier = new type[size];
// ```

// This creates `size` number of objects **on the heap**.
// Each element is constructed automatically.

// ---

// ## ✔ **3. Requires a Default Constructor**

// Same rule as static arrays:

// If the class has a parameterized constructor but **no default constructor**, this will fail:

// ```cpp
// identifier = new Type[10];   // ❌ Requires default constructor
// ```

// Because C++ needs to call a constructor without arguments for each element.

// ---

// ## ✔ **4. Accessing elements**

// Same as static arrays — using index + dot operator:

// ```cpp
// identifier[0].printDetails();
// identifier[2].start();
// ```

// ---

// ## ✔ **5. Array is located on the heap**

// This means:

// * You must explicitly delete it using `delete[]`
// * It survives after function exits (until deleted)
// * Useful for large or runtime-determined sizes

// ---

// # ⭐ Example Code (Interview Friendly)

// ```cpp
#include <iostream>
using namespace std;

class Car {
public:
    Car() {
        cout << "Car created\n";
    }

    void drive() {
        cout << "Car is driving\n";
    }
};

int main() {
    int n;
    cout << "Enter number of cars: ";
    cin >> n;

    Car* cars = new Car[n];   // Dynamic array on heap

    cars[0].drive();
    cars[1].drive();

    delete[] cars;            // Must delete to avoid memory leak
}
// ```

// ---

// # 🔥 Interview-Level Summary

// **Q: What is a dynamic array of objects?**
// A dynamic array is an array whose size is decided at runtime and whose memory is allocated on the heap using `new`.

// **Q: Why do we need a default constructor?**
// Because C++ must create each element without arguments when we do `new Type[size]`.

// **Q: How to access object members?**
// Using:

// ```cpp
// identifier[i].memberFunction();
// ```

// **Q: Where is the array stored?**
// On the **heap**.

// **Q: What must we do after using it?**

// ```cpp
// delete[] identifier;
// ```

// ---

// If you want, I can also prepare a **combined slide** comparing:

// ### Static Array vs Dynamic Array of Objects

// (with diagrams + interview points).




// Not exactly — **you do NOT get an array of pointers** when you write this:

// ```cpp
// Car* cars = new Car[size];
// ```

// Let’s clear this confusion properly 👇

// ---

// # ✅ **This is NOT an array of pointers**

// ```cpp
// Car* cars = new Car[size];
// ```

// Here:

// * `cars` is a **single pointer** that points to the **first element**.
// * `cars[i]` is a **full Car object**, not a pointer.
// * The array elements are **objects stored on the heap**, not pointers.

// So:

// ```
// cars → [Car][Car][Car][Car]...
// ```

// Each `[Car]` is a real object fully constructed.

// ---

// # ❌ Array of Pointers Looks Like This

// If you want an *array of pointers*, you must write:

// ```cpp
// Car** cars = new Car*[size];   // array of pointers

// cars[0] = new Car();           // manually allocate each object
// cars[1] = new Car();
// ```

// Here:

// * `cars` = pointer to array
// * `cars[i]` = pointer to a Car object
// * You must call `new` again for each element

// Diagram:

// ```
// cars → [*][*][*][*]...
//            ↓   ↓   ↓
//           Car Car Car
// ```

// ---

// # 🔥 **Difference (Simple Table)**

// | Expression               | What It Creates                   | Elements hold |
// | ------------------------ | --------------------------------- | ------------- |
// | `Car* a = new Car[n];`   | Dynamic array of **Car objects**  | Objects       |
// | `Car** b = new Car*[n];` | Dynamic array of **Car pointers** | Pointers      |

// ---

// # 🔍 Why Your Slide Uses `Car* arr = new Car[size];`?

// Because C++ **returns a pointer** to the first element of the array.
// But this does *not* mean the array holds pointers.

// ---

// # ✔ Example (NOT array of pointers)

// ```cpp
// Car* arr = new Car[5]; // 5 Car objects
// arr[0].drive();        // works
// ```

// # ❌ Example (array of pointers)

// ```cpp
// Car** arr = new Car*[5]; // 5 pointers, NOT objects
// arr[0] = new Car();      // must create object yourself
// arr[0]->drive();
// ```

// ---

// # ⭐ Final Answer

// 👉 **`T* arr = new T[size];` creates a dynamic array of objects, NOT an array of pointers.**
// 👉 To create an array of pointers, you must use `T**`.

// ---
