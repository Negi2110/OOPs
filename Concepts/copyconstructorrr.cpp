// Here is the **clean, interview-ready explanation + commented code** for the **Delete Specifier (`= delete`)** based on your slide.

// ---

// # ✅ **Delete Specifier (C++11) – Interview Notes**

// ### **What is `= delete`?**

// `= delete` tells the compiler:

// > “This function must NOT be generated, called, or defined.”

// It prevents:

// * Automatic generation of the function
// * Accidental invocation of that function
// * Compiler from creating a default version

// Most commonly used to disable:

// * Copy constructor
// * Copy assignment operator
// * Move operations
// * Certain overloads

// ---

// # 🧠 **Why is it useful?**

// Sometimes you want a class to be **non-copyable**.

// Why?

// * The class owns resources (file handles, sockets, threads)
// * Copying would cause two objects to “own” the same resource → dangerous
// * Many modern C++ types (e.g., `std::unique_ptr`) delete their copy constructor

// ---

// # ✅ **Code Example (With Comments)**

// ```cpp
#include <iostream>
using namespace std;

class GameObject {
public:
    // Delete the copy constructor
    // This prevents the object from being copied.
    GameObject(const GameObject&) = delete;
    
    GameObject() {
        cout << "Default constructor called" << endl;
    }
};

int main() {
    GameObject obj1;          // ✔ OK: default constructor

    GameObject obj2(obj1);    // ❌ ERROR: copy constructor is deleted
                              // This line will NOT compile
    
    return 0;
}
// ```

// ---

// # ❌ **Why does this NOT compile?**

// Because:

// ```cpp
// GameObject(const GameObject&) = delete;
// ```

// explicitly tells the compiler:

// > “If anyone tries to copy this object, throw a compile-time error.”

// So this line is illegal:

// ```cpp
// GameObject obj2(obj1);   // ❌ Copy constructor cannot be invoked
// ```

// ---

// # 📌 **Common Interview Use Cases**

// Classes that delete the copy constructor:

// ### ✔ `std::unique_ptr`

// Cannot be copied — ownership cannot be shared.

// ### ✔ RAII resource holders

// Classes managing:

// * Mutexes
// * File handles
// * Network sockets
// * GPU resources

// These should **not be copied**, only moved.

// ---

// # 📌 **Copy-Paste Interview Summary**

// * `= delete` prevents a function from being generated or used.
// * Often used to disable copying:

//   ```cpp
//   ClassName(const ClassName&) = delete;
//   ClassName& operator=(const ClassName&) = delete;
//   ```
// * Trying to copy such an object results in a **compile-time error**.
// * Used for resource-owning classes to prevent double-free, leaks, and invalid ownership.

// ---

// If you want, I can also explain:

// ✔ delete vs private copy constructor (old C++03 method)
// ✔ how move constructors work when copy is deleted
// ✔ real-world usage examples (unique_ptr, file handles, threads)
