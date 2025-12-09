/// ## ✅ What Is a *Friend Class*? (Simple Meaning)

// * Just like a **friend function**, a **friend class** is also given **special access**.
// * A **friend class can access:**

//   * ✅ private members
//   * ✅ protected members
//     of another class.
// * This access is given using:

// ```cpp
// friend class ClassName;
// ```

// ---

// ## ✅ Key Rule from the Slide

// ```cpp
// class A {
//     friend class B;
// };
// ```

// This means:

// > ✅ **Class `B` can directly access the private and protected members of class `A`.**

// But:

// * ❌ `A` does **NOT** automatically get access to `B`
// * ❌ Friendship is **NOT mutual**
// * ❌ Friendship is **NOT inherited**

// ---

// ## ✅ Fully Commented Friend Class Example

// ```cpp
#include <iostream>
#include <string>
using namespace std;

/*
====================================================
CLASS A (THE CLASS THAT GIVES FRIEND ACCESS)
====================================================
*/

class A {
private:
    int secretValue;   // ✅ PRIVATE data

protected:
    int protectedValue; // ✅ PROTECTED data

public:
    A() : secretValue(100), protectedValue(200) {}

    // ✅ Declaring class B as a FRIEND
    friend class B;
};


/*
====================================================
CLASS B (THE FRIEND CLASS)
====================================================
- Because B is declared as FRIEND inside class A,
  it can directly access:
  ✅ A::secretValue (private)
  ✅ A::protectedValue (protected)
*/

class B {
public:
    void showValues(A& obj) {

        // ✅ Legal access because B is a FRIEND of A
        cout << "Private value from A = " << obj.secretValue << endl;
        cout << "Protected value from A = " << obj.protectedValue << endl;
    }
};


/*
====================================================
MAIN FUNCTION (TESTING)
====================================================
*/

int main() {

    A objA;     // Object of class A
    B objB;     // Object of class B

    // ✅ B can access A's private & protected data
    objB.showValues(objA);

    return 0;
}


// ## ✅ What This Program Proves (Interview Points)

// * ✅ `secretValue` is **PRIVATE**
// * ✅ `protectedValue` is **PROTECTED**
// * ✅ Normally, neither is accessible outside `A`
// * ✅ But because:

//   ```cpp
//   friend class B;
//   ```

//   class `B` can access both
// * ✅ This is a **controlled break of encapsulation**

// ---

// ## ✅ Important Interview Rules for Friend Classes

// * ✅ Friendship is **one-way**
// * ✅ Friendship is **NOT inherited**
// * ✅ Friendship is **NOT transitive**
// * ✅ A friend class is **NOT a derived class**
// * ✅ Friend is used for:

//   * Managers
//   * Debug tools
//   * Serialization systems
//   * Engine-level access

// ---

// ## 🔥 One-Line Interview Finisher

// > “A friend class is a class that is explicitly allowed to access another class’s private and protected members using the `friend` keyword.”

// ---

// A friend function gives a single external function access to a class’s private and protected members, while a friend class gives all member functions of another class that same access; for example, in a Manager–Entity engine pattern, an EntityManager is often declared a friend of Entity so it can directly modify internal state like IDs, transforms,
//  or lifecycle flags for performance and control. Friendship is powerful because it bypasses encapsulation, enabling fast access, tight coupling, and clean operator overloading or engine-level control—but it is also dangerous because it breaks data hiding, increases coupling, and makes maintenance harder if overused.
//   A common interview trick is that friendship is NOT inherited and NOT mutual: if B is a friend of A, C (derived from B) is not automatically a friend of A, and A does not gain access to B—friendship works only in the exact direction it is declared.