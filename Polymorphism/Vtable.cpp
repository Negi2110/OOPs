// Perfect — I’ll rewrite this **exact example in clean C++ with deep interview-level comments inside the code itself**. This version explains **vtable, vptr, overriding, late binding, memory layout, and polymorphism** exactly how interviewers expect.

// ```cpp
#include <iostream>
using namespace std;

/*
===========================================
BASE CLASS
===========================================
- Since this class has at least ONE virtual function,
  the compiler will:
  ✅ Create a vtable for this class
  ✅ Add a hidden pointer (vptr) inside every object of this class
*/

class Model {
public:
    // ✅ Virtual function → Goes into vtable
    virtual void Update() {
        cout << "Update Model\n";
    }

    // ✅ Virtual function → Also goes into vtable
    virtual void Draw() {
        cout << "Draw Model\n";
    }

    /*
    🔹 Internally generated (NOT written by programmer):

    struct Model {
        void** vptr;   <-- hidden pointer added by compiler
        // other data members...
    };

    🔹 Model vtable looks like:
    --------------------------
    | &Model::Update |
    | &Model::Draw   |
    --------------------------
    */
};


/*
===========================================
DERIVED CLASS 1
===========================================
- Inherits from Model
- Overrides ONLY Draw()
- Gets its OWN vtable
*/

class Car : public Model {
public:
    // ❌ Update() is NOT overridden → Uses Model::Update
    // ✅ Draw() is overridden → Goes into Car vtable

    void Draw() override {   // override is optional but recommended
        cout << "Draw Car\n";
    }

    /*
    🔹 Car vtable looks like:
    --------------------------
    | &Model::Update |  <-- inherited
    | &Car::Draw     |  <-- overridden
    --------------------------

    ✅ This proves:
       vtable always stores the MOST DERIVED version of functions
    */
};


/*
===========================================
DERIVED CLASS 2
===========================================
- Overrides BOTH Update() and Draw()
- Gets a completely different vtable
*/

class Plane : public Model {
public:
    void Update() override {
        cout << "Update Plane\n";
    }

    void Draw() override {
        cout << "Draw Plane\n";
    }

    /*
    🔹 Plane vtable looks like:
    --------------------------
    | &Plane::Update |
    | &Plane::Draw   |
    --------------------------
    */
};


int main() {

    // ✅ Base class pointer holding Derived object
    Model* m1 = new Car();
    Model* m2 = new Plane();

    /*
    🔹 MEMORY AT RUNTIME:

    m1 → vptr → Car vtable
    m2 → vptr → Plane vtable

    ✅ Even though pointer type is Model*
       the vptr decides which function runs.
    */

    m1->Update();   // ✅ Model::Update (Car did NOT override it)
    m1->Draw();     // ✅ Car::Draw (runtime binding via vtable)

    cout << "-----------------\n";

    m2->Update();   // ✅ Plane::Update
    m2->Draw();     // ✅ Plane::Draw

    /*
    ✅ This is RUNTIME POLYMORPHISM
    ✅ Function call is resolved using vptr + vtable
    ✅ This is called LATE BINDING / DYNAMIC DISPATCH
    */

    delete m1;
    delete m2;

    return 0;
}
// ```

// ---

// ## ✅ EXACT INTERVIEW CONCEPTS THIS CODE DEMONSTRATES

// | Concept             | Proved in Code                           |
// | ------------------- | ---------------------------------------- |
// | vtable              | Created for `Model`, `Car`, `Plane`      |
// | vptr                | Hidden inside every object               |
// | Runtime binding     | `Model*` calling derived functions       |
// | Late binding        | Call resolved at runtime                 |
// | Function overriding | `Car::Draw`, `Plane::Draw`               |
// | Most derived rule   | vtable stores derived versions           |
// | Compile vs runtime  | vtable built at compile, used at runtime |

// ---

// ## 🔥 ONE-LINE INTERVIEW PUNCHLINE

// > “Even though the pointer is of base type, the **vptr inside the object points to the derived vtable**, which ensures that the **most derived function is called at runtime**.”

// ---


// ---

// ### ✅ Correct Concept (Polished Interview Version)

// > At **compile time**, the compiler **creates a vtable for any class that has at least one virtual function**.
// > If a **derived class overrides** that virtual function, the **derived function’s address is placed in its vtable**.
// > At **runtime**, when a **base class pointer points to a derived object**, the **vptr inside the object points to the derived class’s vtable**.
// > If the function **is overridden**, the **derived version is called**.
// > If the function **is NOT overridden**, the **base class version is called**.

// ✅ This is exactly **runtime polymorphism / late binding / dynamic dispatch**.

// ---

// ### 🔥 Ultra-Compact 1-Line Version (for rapid interviews)

// > “The vtable is built at compile time, but at runtime the object’s vptr selects either the base or the overridden derived function depending on what’s overridden.”

// ---


// The vptr is generated for every object of a class that has at least one virtual function, and this automatically applies to all of its derived (child) classes as well — even if the child class does not declare any new virtual functions.

// If a class has no inheritance and no virtual functions, then the compiler does NOT create any vtable and the objects of that class do NOT contain a vptr.