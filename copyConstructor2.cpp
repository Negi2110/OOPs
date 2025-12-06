// Here is a **clean, interview-ready version** of everything in your slide, written as **comments inside a class**, exactly how interviewers like to see it:

// ---

// ## ✅ **Copy Constructor – Full Class with Clear Comments**

// ```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int value;

public:

    // --------------------------------------------------------
    // 1️⃣ NORMAL CONSTRUCTOR
    // --------------------------------------------------------
    MyClass(int v) : value(v) {
        cout << "Normal constructor called" << endl;
    }

    // --------------------------------------------------------
    // 2️⃣ COPY CONSTRUCTOR
    //
    // • Has the SAME name as the class.
    // • Takes ONE argument:
    //     --> const MyClass& (a reference to an object of same class)
    // • Used to create a new object as a COPY of an existing object.
    //
    // Signature:
    //     MyClass(const MyClass& obj)
    //
    // --------------------------------------------------------
    MyClass(const MyClass& obj) {
        cout << "Copy constructor called" << endl;

        // Copy member variables from 'obj' into the new object.
        this->value = obj.value;
    }

    int getValue() const {
        return value;
    }
};

int main() {

    // --------------------------------------------------------
    // 📌 COPY CONSTRUCTOR INVOCATION CASE 1:
    // Initialize one object from another of same type
    // --------------------------------------------------------
    MyClass obj1(10);
    MyClass obj2 = obj1;   // Copy constructor called


    // --------------------------------------------------------
    // 📌 COPY CONSTRUCTOR INVOCATION CASE 2:
    // Passing object BY VALUE to a function
    // (Uncomment to test)
    //
    // void func(MyClass temp);  // temp created via copy constructor
    // func(obj1);
    // --------------------------------------------------------


    // --------------------------------------------------------
    // 📌 COPY CONSTRUCTOR INVOCATION CASE 3:
    // Returning object BY VALUE from a function
    // (again will call copy constructor)
    //
    // MyClass create() { MyClass t(5); return t; }
    // MyClass obj3 = create();
    // --------------------------------------------------------


    // --------------------------------------------------------
    // 📌 COPY CONSTRUCTOR INVOCATION CASE 4:
    // Initializing elements in a sequential container
    //
    // vector<MyClass> v(3, obj1); // Each element is a copy → copy ctor
    // --------------------------------------------------------


    // --------------------------------------------------------
    // 📌 COPY CONSTRUCTOR INVOCATION CASE 5:
    // Initializing array elements using an initializer list
    //
    // MyClass arr[2] = { obj1, obj2 }; // Copy constructor called twice
    // --------------------------------------------------------

    return 0;
}
// ```

// ---

// # 📌 **Copy-Paste Interview Summary (based on your slide)**

// ### ✔ Copy constructor is a special constructor used to **create a new object by copying an existing object**.

// ### ✔ Signature:

// ```cpp
// MyClass(const MyClass& obj)
// ```

// ### ✔ Automatically invoked when:

// 1. Initializing one object from another
// 2. Passing an object **by value**
// 3. Returning an object **by value**
// 4. Initializing elements in sequential containers (vector, list, etc.)
// 5. Initializing elements in arrays using initializer lists

// ### ✔ Compiler provides a default copy constructor (shallow copy) if not written.

