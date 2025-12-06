#include <iostream>
using namespace std;

class MyClass {
public:

    // Default constructor
    MyClass() { }

    // Copy constructor
    MyClass(const MyClass& obj) {
        cout << "Copy constructor invoked" << endl;
    }

    // --------------------------------------------
    // PASS-BY-VALUE ALWAYS triggers copy constructor
    // because a local copy must be created.
    // --------------------------------------------
    void DoSomething(MyClass obj) {
        // obj is a COPY of the argument
    }

    // --------------------------------------------
    // Returning an object BY VALUE also triggers
    // copy constructor (unless optimized).
    // --------------------------------------------
    MyClass ReturnAnObject() {
        MyClass obj;   // local object
        return obj;    // copy constructor invoked (return-by-value)
    }
};

int main() {

    MyClass obj1, obj2;   // Default constructors

    // 1️⃣ Initializing obj3 from obj1
    MyClass obj3(obj1);   // Invokes copy constructor (direct initialization)

    // 2️⃣ Assignment after creation → DOES NOT call copy constructor
    obj3 = obj1;          // Uses copy assignment operator, NOT copy constructor

    // 3️⃣ Another direct initialization
    MyClass obj4 = obj2;  // Invokes copy constructor (copy initialization)

    // 4️⃣ Passing object BY VALUE to a function → invokes copy constructor
    obj2.DoSomething(obj1);

    // 5️⃣ Returning object BY VALUE → invokes copy constructor
    obj2.ReturnAnObject();

    return 0;
}



// **No — that is NOT correct.**
// The copy constructor works for **both static and dynamic objects**, because the copy constructor depends on **HOW the object is created**, not where it is stored (stack vs heap).

// Let me explain clearly.

// ---

// # ✅ **Correct Concept**

// A **copy constructor is used whenever a new object is created from an existing object.**

// This happens in **both** static and dynamic cases.

// ---

// # 🟢 **1. Copy constructor with static objects (YES)**

// ```cpp
// MyClass a;
// MyClass b = a;    // Copy constructor called
// ```

// This is **direct initialization** → copy constructor is used.

// ---

// # 🔵 **2. Copy constructor with dynamic objects (YES — if called)**

// ```cpp
// MyClass a;
// MyClass* p = new MyClass(a);   // Copy constructor is called
// ```

// Here:

// * A **new object** is created on the heap with `new MyClass(a)`
// * Since `a` is passed, copy constructor is used.

// So **copy constructor DOES work with dynamic allocation**.

// ---

// # 🔴 **When people get confused**

// This line:

// ```cpp
// MyClass* ptr = new MyClass;   // NO copy constructor
// ```

// This does **not** call a copy constructor because:

// * No existing object is being copied
// * Only the default constructor is used

// People incorrectly think:

// > “New keyword cannot invoke copy constructor”

// But that's wrong.

// ---

// # 🟢 **Correct dynamic case where copy constructor IS used**

// ```cpp
// MyClass a(10);
// MyClass* ptr = new MyClass(a);   // Copy constructor called
// ```

// This is VALID and calls:

// ✔ copy constructor
// ✔ on a heap-allocated object

// ---

// # 💡 **Golden Rule**

// ### The copy constructor is used when:

// * A **new object** is created
// * AND an **existing object** is used to initialize it

// Not based on:

// * static vs dynamic
// * stack vs heap

// ---

// # 📌 **Summary (Copy-Paste for Interview)**

// * Copy constructor works for **both** stack (static) and heap (dynamic) objects.
// * It is used whenever a **new object is created from another object**.
// * Dynamic allocation calls the copy constructor if you pass an existing object:

//   ```cpp
//   new MyClass(existingObject);
//   ```
// * It is **not** used when simply using:

//   ```cpp
//   new MyClass;   // only default constructor
//   ```

// ---

// If you want, I can give you a table comparing:

// ✔ default constructor
// ✔ copy constructor
// ✔ assignment operator
// ✔ move constructor

// Very useful for interviews!
