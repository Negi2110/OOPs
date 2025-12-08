
#include <iostream>
using namespace std;

/*
====================================================
BASE CLASS
====================================================
- This class is POLYMORPHIC because it has at least
  one virtual function (Draw).
- Being polymorphic is REQUIRED for dynamic_cast to work.
*/

class GameObject {
public:
    GameObject() {}   // Normal constructor

    // ✅ Virtual function → makes this class polymorphic
    virtual void Draw() {}
};


/*
====================================================
DERIVED CLASS
====================================================
- Car inherits from GameObject
- This means: Car "is-a" GameObject
*/

class Car : public GameObject {
public:
    Car() {}   // Normal constructor
};


/*
====================================================
FUNCTION THAT USES DYNAMIC_CAST
====================================================
- Takes a BASE CLASS pointer as parameter
- Tries to convert it into a DERIVED CLASS pointer
- This is called SAFELY DOWNCASTING using dynamic_cast
*/

void f(GameObject* obj) {

    /*
    --------------------------------------------
    SAFE DOWNCAST USING dynamic_cast
    --------------------------------------------
    - We try to convert GameObject* → Car*
    - This works ONLY if obj actually points to a Car object
    - If obj is NOT a Car → dynamic_cast returns nullptr (0)
    */

    Car* car = dynamic_cast<Car*>(obj);  // ✅ Safe runtime check

    /*
    --------------------------------------------
    CHECK WHETHER CAST SUCCEEDED OR FAILED
    --------------------------------------------
    */

    if (car)
        cout << "Valid Cast" << endl;     // ✅ obj was actually a Car
    else
        cout << "Invalid Cast" << endl;   // ❌ obj was NOT a Car
}


/*
====================================================
MAIN FUNCTION
====================================================
*/

int main() {

    /*
    --------------------------------------------
    CASE 1: Passing PURE BASE OBJECT
    --------------------------------------------
    - We create a GameObject
    - It is NOT a Car
    - So dynamic_cast will FAIL
    */

    f(new GameObject());   // ❌ Will print: Invalid Cast


    /*
    --------------------------------------------
    CASE 2: Passing DERIVED OBJECT AS BASE POINTER
    --------------------------------------------
    - We create a Car object
    - Pass it as a GameObject*
    - This is UPCASTING (always safe)
    - Inside f(), dynamic_cast will SUCCEED
    */

    f(new Car());          // ✅ Will print: Valid Cast

    return 0;
}
// ```

// ---

// ## ✅ What This Program PROVES (Interview Points)

// * ✅ `dynamic_cast` is used for **safe downcasting**
// * ✅ It **checks the real object type at runtime**
// * ✅ It **returns `nullptr` if the cast is invalid**
// * ✅ It **requires a polymorphic base class (virtual function required)**
// * ✅ It **prevents crashes and undefined behavior**

// ---

// ## ✅ Expected Output

// ```
// Invalid Cast
// Valid Cast
// ```

// ---

// ## 🔥 One-Line Interview Finisher

// > “This program demonstrates safe runtime downcasting using `dynamic_cast`, which succeeds only when the base pointer actually refers to a derived object.”

// ---
