
#include <iostream>
using namespace std;

/*
====================================================
BASE CLASS (Polymorphic, but static_cast doesn't care)
====================================================
*/

class GameObject {
public:
    GameObject() {}
    virtual void Draw() {
        cout << "GameObject Draw\n";
    }
};


/*
====================================================
DERIVED CLASS
====================================================
*/

class Car : public GameObject {
public:
    int carData = 42;   // extra data – important for illustration

    void Draw() override {
        cout << "Car Draw, carData = " << carData << "\n";
    }
};


/*
====================================================
DANGEROUS FUNCTION USING static_cast
====================================================
- We FORCE a downcast using static_cast.
- There is NO runtime check.
- If obj is NOT actually a Car → UNDEFINED BEHAVIOR.
*/

void f(GameObject* obj) {

    // ❌ This will compile even if obj does NOT point to a Car
    Car* car = static_cast<Car*>(obj);

    /*
    If obj actually points to a GameObject (NOT Car),
    then car points to memory that is NOT a real Car object.

    Accessing car->carData or car->Draw() is now UNDEFINED BEHAVIOR:
    - It might print garbage
    - It might crash
    - It might seem to "work" sometimes (the worst kind of bug)
    */

    cout << "Trying to use car after static_cast...\n";
    car->Draw();                 // ❌ May crash or behave unpredictably
    cout << "carData = " << car->carData << "\n";  // ❌ Also unsafe
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
    - obj is actually a GameObject, NOT a Car
    - But static_cast<Car*> will still "succeed" (no nullptr)
    - Using the pointer is now UNDEFINED BEHAVIOR
    - This is where a crash, garbage, or weird behavior may occur.
    */

    cout << "=== Calling f(new GameObject()) ===\n";
    f(new GameObject());   // ⚠️ DANGEROUS – may crash or misbehave


    /*
    --------------------------------------------
    CASE 2: Passing a REAL Car object
    --------------------------------------------
    - Here static_cast is okay because obj truly is a Car.
    - But the compiler does NOT know the difference between this
      and the previous case – it never checks.
    */

    cout << "\n=== Calling f(new Car()) ===\n";
    f(new Car());          // ✅ Happens to be safe in this call

    return 0;
}
// ```

// ---

// ## 🔍 What’s Going Wrong in CASE 1?

// ```cpp
// GameObject* obj = new GameObject();
// Car* car = static_cast<Car*>(obj);  // ❌ Compiles, but WRONG
// car->Draw();                        // ❌ Undefined behavior
// ```

// * Memory layout of `GameObject` is **smaller/different** than `Car`.
// * But `static_cast` **doesn’t check**.
// * So `car` now **points to a GameObject**, but we **treat it as a Car**.
// * Accessing `carData` or calling `Car::Draw()` expects data that **isn’t there**.
// * Result:

//   * It might print garbage
//   * It might jump to invalid code → **crash**
//   * It might sometimes “work” → **very dangerous bug**

// This is the classic **“looks fine, compiles fine, then randomly dies in production”** situation.

// ---

// ## ✅ Compare with the `dynamic_cast` Version

// With `dynamic_cast`:

// ```cpp
// Car* car = dynamic_cast<Car*>(obj);

// if (car) {
//     // safe to use
// } else {
//     // cast failed – no crash
// }
// ```

// * If `obj` is `new GameObject()` → `car == nullptr`
// * You never dereference an invalid pointer → **no crash**

// ---

// ## 🔥 Interview-Perfect Takeaway

// > “Using `static_cast` for downcasting compiles but performs no runtime check. If the base pointer doesn’t actually point to a derived object, using the result is undefined behavior and can crash. `dynamic_cast` is slower but safe because it checks the real object type and returns `nullptr` when the cast is invalid.”

// If you’d like, next I can:

// * Show a **memory layout diagram** of `GameObject` vs `Car`
// * Show how to **fix this design to avoid downcasting completely** using virtual functions / interfaces.
