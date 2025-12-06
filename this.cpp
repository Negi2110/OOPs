#include <iostream>
using namespace std;

class MyClass {
    // 'value' is a data member (member variable of the object)
    int value;

public:
    // Constructor with a parameter that has the same name as the data member
    MyClass(int value) {
        // 'this' is a pointer to the CURRENT object
        // this->value refers to the object's member variable
        // value (without this->) refers to the constructor parameter
        //
        // Using this-> helps differentiate between:
        //   this->value  → member variable
        //   value        → constructor argument
        this->value = value;
    }

    // Member function to access the value
    // 'this' is also implicitly passed here, although we don’t write it
    int getValue() const {
        return value;  // internally this->value
    }
};

int main() {
    // Creating an object 'obj' of MyClass
    // The constructor receives 10 and assigns it to the object's 'value'
    MyClass obj(10);

    // getValue() prints the stored value (10)
    // Again, 'this' is implicitly used inside getValue()
    cout << obj.getValue() << endl;

    return 0;
}

// this is a pointer to the current object.

// Available only inside class member functions.

// Passed implicitly to every non-static member function.

// Used to distinguish data members from parameters with the same name.

// Example:

// this->value = value; 
// left side = member variable
// right side = constructor parameter