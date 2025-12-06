// # ✅ **Static Arrays of Objects — Explained**

// When you write something like:

// ```cpp
// ClassName arr[5];
// ```

// you are creating a **static array of 5 objects** of type `ClassName`.

// ---

// ## ✔ **1. Objects are created automatically**

// In a static array:

// ```cpp
// ClassName arr[5];
// ```

// all 5 objects (`arr[0]` to `arr[4]`) are **constructed automatically** as soon as the program reaches this line.

// There is **no need for `new`**.

// ---

// ## ✔ **2. Requires a Default Constructor**

// If your class has *any* constructor (a parameterized one), and you did **not** write a *default constructor*, this will NOT work:

// ```cpp
// ClassName arr[5];   // ❌ Error if no default constructor exists
// ```

// Because C++ needs a constructor to call **without arguments** for each element in the array.

// So either:

// * write a **default constructor**, or
// * remove all other constructors.

// ---

// ## ✔ **3. Accessing objects**

// You use **array index + dot operator**:

// ```cpp
// arr[2].printDetails();
// arr[0].setValue(10);
// ```

// ---

// # ⭐ Example Code
#include <iostream>
using namespace std;

class Car {
public:
    Car() {                // Default constructor REQUIRED
        cout << "Car created\n";
    }

    void drive() {
        cout << "Car is driving\n";
    }
};

int main() {
    Car cars[3];          // Creates 3 Car objects automatically

    cars[0].drive();
    cars[1].drive();
}
// ```
// Car created
// Car created
// Car created
// Car is driving
// Car is driving
// ```

// ---

// # 🔥 Interview-Level Explanation

// **Q: What is a static array of objects?**
// A static array of objects is a fixed-size array in which each element is an object. All objects are created automatically when the array is declared.

// **Q: Why do we need a default constructor?**
// Because C++ must construct each element without any arguments. Without a default constructor, object creation fails.

// **Q: How do we call member functions?**
// Using the dot operator on an indexed element:

// ```cpp
// arr[i].function();
// ```

// ---

