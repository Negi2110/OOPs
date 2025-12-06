#include <iostream>
using namespace std;

// Simple Data class that stores an integer
class Data {
public:
    int data;

    // Constructor to initialize 'data'
    Data(int d) : data(d) {}
};

// Class demonstrating SHALLOW COPY behavior
class ShallowClass {
public:
    Data* value;   // Pointer to dynamically allocated Data

    // Default Constructor
    ShallowClass() {
        value = new Data(0);   // Allocate new Data object
    }

    // Shallow Copy Constructor
    // Copies ONLY the pointer -> both objects share the SAME memory
    ShallowClass(const ShallowClass& c) {
        this->value = c.value;  // Shallow copy (pointer copied, not the data)
    }
};

int main() {

    ShallowClass obj1;          // obj1.value -> points to Data(0)

    ShallowClass obj2(obj1);    // Copy Constructor -> shallow copy
    ShallowClass obj3 = obj2;   // Copy Constructor -> shallow copy

    // Modify the value using obj1
    obj1.value->data = 25;

    // Because the pointer was shallow copied, all objects point to the SAME Data object
    cout << "Obj1.value->data : " << obj1.value->data << endl;  // 25
    cout << "Obj2.value->data : " << obj2.value->data << endl;  // 25
    cout << "Obj3.value->data : " << obj3.value->data << endl;  // 25

    return 0;
}


// 🧠 Explanation (Why Output is 25 for All)
// ✔ Shallow copy copies pointer addresses
// this->value = c.value;


// Meaning:

// obj1.value ───► [ Data object ]
// obj2.value ───┘
// obj3.value ───┘


// All three point to the same Data object.

// So:

// obj1.value->data = 25;


// changes the shared memory, so all objects print 25.

// ⚠️ Problems with Shallow Copy

// Objects share memory → modifying one changes all

// Destructor will delete memory multiple times → double delete crash

// Not safe with dynamic allocation