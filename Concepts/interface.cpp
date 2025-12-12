#include <iostream>
using namespace std;

// -------------------------------------------------------------
// Interface (Abstract Class)
// -------------------------------------------------------------
// An interface in C++ is created using a class that contains
// only pure virtual functions. It defines a contract but provides
// no implementation.
// -------------------------------------------------------------
class IPrintable {
public:
    virtual void Print() const = 0;  // Pure virtual → interface method
    virtual ~IPrintable() = default; // Always provide virtual destructor
};

// -------------------------------------------------------------
// Concrete Class implementing the Interface
// -------------------------------------------------------------
// GameObject MUST implement Print(), because it inherits IPrintable.
// -------------------------------------------------------------
class GameObject : public IPrintable {
private:
    int id;

public:
    explicit GameObject(int id) : id(id) {}

    int GetID() const {
        return id;
    }

    // Implementation of interface function
    void Print() const override {
        cout << "GameObject ID: " << id << endl;
    }
};

// -------------------------------------------------------------
// MAIN - Demonstrates how interface pointers enable polymorphism
// -------------------------------------------------------------
int main() {

    // ✔ Normal object - Full access to class methods
    GameObject* obj1 = new GameObject(1);
    cout << "Using GameObject pointer:" << endl;
    cout << "ID: " << obj1->GetID() << endl;   // Allowed
    obj1->Print();                             // Allowed
    cout << endl;

    // ✔ Interface pointer - Polymorphism
    IPrintable* obj2 = new GameObject(2);
    cout << "Using IPrintable (Interface) pointer:" << endl;

    // obj2->GetID();  // ❌ Not allowed: Interface does not define GetID()
    obj2->Print();     // ✔ Allowed: part of the interface

    delete obj1;
    delete obj2;

    return 0;
}


// Below is the **perfect interview explanation** for the image you posted.
// This is clean, accurate, and exactly what an interviewer expects.

// ---

// # ⭐ INTERVIEW ANSWER — Interface Example in C++

// ### **1. What is happening in this example?**

// In C++, an **interface** is created using a class that contains **only pure virtual functions**:

// ```cpp
// class IPrintable {
// public:
//     virtual void Print() = 0;   // pure virtual function → interface
// };
// ```

// This means:

// * You **cannot create an object** of `IPrintable`
// * Any class inheriting it **must implement** `Print()`
// * This forms a **contract** (interface)

// ---

// # ⭐ **2. The derived class implements the interface**

// ```cpp
// class GameObject : public IPrintable {
// private:
//     int id;

// public:
//     GameObject(int id) : id(id) {}

//     int GetID() const {
//         return id;
//     }

//     void Print() override {
//         cout << "ID: " << id << endl;
//     }
// };
// ```

// ### Key points:

// * `GameObject` **inherits** from `IPrintable`
// * It provides its own implementation of `Print()`
// * Now `GameObject` objects can be treated as `IPrintable` objects

// ---

// # ⭐ **3. Main function demonstrates polymorphism**

// ```cpp
// int main() {
//     GameObject *obj1 = new GameObject(1);
//     cout << obj1->GetID() << endl;

//     IPrintable *obj2 = new GameObject(2);
//     obj2->Print();
// }
// ```

// ### 🍀 Important behaviors shown:

// ### **A. Normal object usage**

// ```cpp
// GameObject* obj1 = new GameObject(1);
// obj1->GetID();     // allowed
// obj1->Print();     // allowed
// ```

// Since the pointer type is `GameObject*`,
// all public methods are accessible.

// ---

// ### **B. Using Interface Pointer**

// ```cpp
// IPrintable *obj2 = new GameObject(2);
// obj2->Print();     // allowed
// ```

// But:

// ```cpp
// obj2->GetID();     // ❌ NOT allowed
// ```

// Because interface pointers can only access **interface-defined functions**, not functions added by derived classes.

// ---

// # ⭐ **Interview Summary (Use This)**

// > **“An interface in C++ is implemented using a class with pure virtual functions.
// > Here, `IPrintable` acts as an interface because it contains only a pure virtual function `Print()`.
// > `GameObject` publicly inherits this interface and provides its implementation.
// >
// > We cannot create objects of `IPrintable`, but we can create pointers to it.
// > This allows us to use runtime polymorphism—`IPrintable*` can point to any class that implements the interface, but it only exposes the methods defined in the interface.
// >
// > This helps enforce a contract, restricts access, and makes the code loosely coupled and extensible.”**

// ---

