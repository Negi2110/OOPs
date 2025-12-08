
#include <iostream>
using namespace std;

/*
====================================
BASE CLASS
====================================
- Has a virtual function Update()
- This creates a vtable entry
*/

class GameObject {
public:
    virtual void Update() {
        cout << "Game Object Update" << endl;
    }
};


/*
====================================
DERIVED CLASS
====================================
- Inherits from GameObject
- Uses override keyword
- This tells the compiler:
  "This function MUST override a virtual function"
*/

class Car : public GameObject {
public:
    void Update() override {   // ✅ Correct override
        cout << "Car Update" << endl;
    }
};


int main() {

    GameObject* obj = new Car();

    obj->Update();   // ✅ Calls Car::Update() (runtime polymorphism)

    delete obj;
    return 0;
}
// ```

// ---

// ## ✅ Why NO Compiler Error Happens Here

// Because all **override rules are satisfied**:

// | Rule                       | Status   |
// | -------------------------- | -------- |
// | Base function is `virtual` | ✅ Yes    |
// | Same function name         | ✅ Update |
// | Same parameters            | ✅ None   |
// | Same return type           | ✅ void   |
// | Access level compatible    | ✅ public |

// ✅ Therefore:

// * `Car::Update()` is a **true override**
// * Compiler **accepts it**
// * vtable entry for `Update` now points to `Car::Update`
// * Runtime polymorphism works perfectly

// ---

// ## ✅ What Would Cause a Compiler Error Here?

// If you wrote:

// ```cpp
// void Update(int x) override { }   // ❌ ERROR
// ```

// Then:

// * Signature mismatch
// * No matching virtual in base
// * `override` triggers compiler error
// * 🔥 Bug caught at compile time

// ---

// ## ✅ Final One-Line Interview Summary

// > “In this example, no compiler error occurs because `Car::Update()` exactly matches `GameObject::Update()`, so it is a valid override.”

// ---

