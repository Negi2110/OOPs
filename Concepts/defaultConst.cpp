#include <iostream>
using namespace std;

class Model {
public:
    Model() {
        // Base class constructor
        // In inheritance, this constructor is always called FIRST
        // whenever an object of the derived class is created.
        cout << "model constructor invoked" << endl;
    }
};

class Car : public Model {
public:
    Car() {
        // Derived class constructor
        // This runs AFTER the base class constructor finishes.
        cout << "car constructor invoked" << endl;
    }
};

int main() {
    // Creating a derived class object using dynamic allocation.
    // Even when using 'new', constructor call order remains the same:
    // 1. Base class constructor (Model)
    // 2. Derived class constructor (Car)

    Car *is_object = new Car();

    // Output:
    // model constructor invoked
    // car constructor invoked

    return 0;
}
// 1. Constructor calling order in inheritance

// When an object of a derived class (Car) is created, constructors are called in the order of inheritance, i.e.:

// Base class constructor executes first

// Derived class constructor executes next

// This happens automatically even if you do not explicitly call the base constructor.

// 2. Why base constructor runs first

// The derived class depends on the base class.

// So C++ ensures the base part of the object is fully constructed first.

// Only then the derived part can safely initialize its own members.

// This ensures object consistency and avoids undefined behavior.

// Dynamic object creation does NOT change constructor order

// Even though the object is created using new:

// Car* is_object = new Car();


// The constructor order remains the same.

// Memory allocation happens first → then constructors execute from base → derived.

// 5. Key Interview Points

// Constructors in inheritance follow a top-down order:
// Base → Derived

// Destructors follow the reverse order:
// Derived → Base

// If a base class has parameters, the derived constructor must explicitly call it using an initializer list: