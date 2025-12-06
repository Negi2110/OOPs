#include <iostream>
using namespace std;

/*
    INTERVIEW NOTES:
    ----------------
    - A virtual function enables *runtime polymorphism*.
    - Without 'virtual', function calls use *static binding* (compile time).
    - With 'virtual', C++ uses *dynamic binding* (runtime dispatch).
    - When a base-class pointer points to a derived object,
      and the function is virtual, the *derived* function is called.
*/

class Model {
public:
    // Marked virtual → enables dynamic dispatch (runtime binding)
    virtual void Draw() {
        cout << "Draw Model\n";
    }
};

class Car : public Model {
public:
    // Same signature → this function overrides Model::Draw()
    void Draw() override {
        cout << "Draw Car\n";
    }
};

int main() {

    // --- CASE 1: Base pointer → Derived object (THIS IS POLYMORPHISM) ---
    Model* model = new Car();  

    /*
        EXPECTED OUTPUT: Draw Car

        WHY?
        ----
        - Pointer type = Model*
        - Actual object type = Car
        - Draw() is virtual in Model
          → so C++ checks the ACTUAL object type at runtime
          → and calls Car::Draw()
    */
    model->Draw();


    // --- CASE 2: Derived pointer → Derived object (normal call, no polymorphism needed) ---
    Car* car = new Car();
    car->Draw();   // OUTPUT: Draw Car

    delete model;
    delete car;

    return 0;
}


// 🖥️ Correct Output
// Draw Car
// Draw Car

// 🔥 Interview Explanation: Why virtual is required?

// If we remove virtual from:

// virtual void Draw()


// then this call:

// Model* model = new Car();
// model->Draw();


// will output:

// Draw Model


// because:

// Without virtual, C++ chooses the function based on pointer type, not object type

// Pointer type = Model* → so it calls Model::Draw()

// This is static binding (compile-time)

// ⭐ What the interviewer expects you to say

// A virtual function allows C++ to decide which function to call at runtime based on the actual object type, not the pointer type. Without virtual, the base-class version always runs, even if the pointer refers to a derived object.

// 🎯 Additional Interview Notes (Very Important)
// ✔ 1. Virtual enables dynamic binding

// Base pointer → Derived object → calls derived method.

// ✔ 2. Override must match signature

// Otherwise you hide the method, not override.

// ✔ 3. Polymorphism works only with pointers or references

// Not with objects by value (object slicing).

// ✔ 4. Always use a virtual destructor in base classes

// To avoid memory leaks when deleting derived via base pointer.




// Great question — and this is EXACTLY where many students get confused in polymorphism.

// Let’s answer it **cleanly and simply**:

// ---

// # ✅ **Case: No `virtual` keyword + Car pointer**

// ### Code:

// ```cpp
// class Model {
// public:
//     void Draw() { cout << "Draw Model"; }
// };

// class Car : public Model {
// public:
//     void Draw() { cout << "Draw Car"; }
// };

// int main() {
//     Car* car = new Car();
//     car->Draw();
// }
// ```

// ---

// # ✔ **Output:**

// ```
// Draw Car
// ```

// ---

// # 🤔 **WHY?**

// Because if you call a function using:

// * A **Car pointer**, AND
// * The object is **Car**

// then C++ **clearly knows** which function to call → it will call **Car::Draw()**.

// This does NOT require polymorphism or `virtual`.

// This is **normal function overriding**, not runtime polymorphism.

// ---

// # 🔥 **Important Rule (Simple)**

// | Pointer Type | Object Type | virtual needed? | Function Called |
// | ------------ | ----------- | --------------- | --------------- |
// | **Car***     | Car         | ❌ No            | **Car::Draw()** |
// | **Model***   | Car         | ✅ Yes           | Car::Draw()     |
// | **Model***   | Car         | ❌ No            | Model::Draw()   |

// ---

// # 📌 When `virtual` matters

// ### The ONLY time `virtual` changes behavior is when:

// ```cpp
// Model* ptr = new Car();
// ptr->Draw();
// ```

// Without virtual → `Draw Model`
// With virtual → `Draw Car`

// ---

// # 🧠 Why Car* → Car ALWAYS calls Car::Draw()

// Because:

// * No polymorphism needed
// * No ambiguity
// * It’s direct function overriding
// * Compiler knows everything at compile time

// This is **static binding**, but still correct based on *actual pointer type*.

// ---

// # ⭐ Final takeaway

// > **If the pointer type is the same as the object type, the derived function will always be called — even without `virtual`.**

// `virtual` is only needed when a **base pointer** points to a **derived object**.

// ---

// If you want, I can also explain:

// 🔹 What if the function signatures differ?
// 🔹 What if parameters differ?
// 🔹 What if you hide the function?
// 🔹 When overriding becomes hiding?

// Just ask: **“Explain overriding vs hiding”** or **“Explain what happens with different signatures.”**
