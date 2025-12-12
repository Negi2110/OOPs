// ## ✅ **Full Class Example with Copy Constructor + Comments**

// ```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int id;        // Normal (non-pointer) data member
    int* data;     // Pointer data member (to demonstrate shallow vs deep copy)

public:

    // -------------------------------------------
    // 1️⃣ Normal Constructor
    // Initializes data members
    // -------------------------------------------
    MyClass(int value, int d) {
        id = value;

        // Allocating memory on heap
        // Important for explaining shallow vs deep copy
        data = new int(d);

        cout << "Normal constructor called" << endl;
    }

    // -------------------------------------------
    // 2️⃣ Copy Constructor
    // Initializes an object using ANOTHER object
    // Called automatically during:
    //   - object copy
    //   - pass by value
    //   - return by value
    //
    // If we DON'T define this, compiler provides
    // a DEFAULT copy constructor (shallow copy).
    // -------------------------------------------
    MyClass(const MyClass& obj) {
        cout << "Copy constructor called" << endl;

        // Copy normal data members (OK)
        id = obj.id;

        // ❗️ SHALLOW COPY WARNING (default behavior):
        // data = obj.data;
        //
        // This would copy only the ADDRESS → both objects
        // point to the same memory → dangerous.
        // So instead we do DEEP copy:

        data = new int(*obj.data);   // Deep copy to avoid shared memory
    }

    // -------------------------------------------
    // Getter functions
    // -------------------------------------------
    int getId() const { return id; }
    int getData() const { return *data; }

    // -------------------------------------------
    // Destructor
    // Frees dynamically allocated memory.
    // Important because shallow copies cause double-delete!
    // -------------------------------------------
    ~MyClass() {
        delete data;
        cout << "Destructor called" << endl;
    }
};

int main() {

    // Create object using normal constructor
    MyClass obj1(10, 50);

    // Create a NEW object as a COPY of obj1
    // This invokes the COPY CONSTRUCTOR
    MyClass obj2 = obj1;

    cout << obj1.getId() << " " << obj1.getData() << endl;
    cout << obj2.getId() << " " << obj2.getData() << endl;

    return 0;
}
// ```

// ---

// ## 📌 **What This Code Demonstrates (Interview Points Inside Comments)**

// ✔ What a **copy constructor** is
// ✔ When the compiler invokes it
// ✔ Default copy constructor = shallow copy
// ✔ Why shallow copy is dangerous (pointer sharing)
// ✔ How to implement a **deep copy**
// ✔ How destructors relate to shallow copying (double delete)
// ✔ Fully commented explanation inside code

// ---

// If you want, I can also write a **Shallow Copy vs Deep Copy** code comparison for interviews.
