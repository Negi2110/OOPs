#include <iostream>
using namespace std;

// Simple Data class storing a single integer
class Data {
public:
    int data;

    Data(int d) : data(d) { }
};

// Class demonstrating DEEP COPY behavior
class DeepClass {
public:
    Data* value;

    // Default constructor -> allocate new Data object
    DeepClass() {
        value = new Data(0);
    }

    // Deep Copy Constructor
    // Allocates NEW memory and copies the VALUE (not the pointer)
    DeepClass(const DeepClass& c) {
        this->value = new Data(c.value->data);
    }
};

int main() {

    DeepClass obj1;             // obj1.value -> Data(0)

    DeepClass obj2(obj1);       // Deep copy -> new Data object created
    DeepClass obj3 = obj2;      // Deep copy -> new Data object created

    // Modify obj1's value
    obj1.value->data = 25;

    // Deep copies DO NOT share memory
    cout << "Obj1.value->data : " << obj1.value->data << endl;  // 25
    cout << "Obj2.value->data : " << obj2.value->data << endl;  // 0
    cout << "Obj3.value->data : " << obj3.value->data << endl;  // 0

    return 0;
}



// 🧠 Explanation: Why only obj1 changes
// ✔ Deep Copy = New memory allocated for each object

// In the copy constructor:

// this->value = new Data(c.value->data);


// Each object gets its own Data object:

// obj1.value ───► [ 25 ]
// obj2.value ───► [ 0 ]
// obj3.value ───► [ 0 ]


// They are independent, so changing one does not affect the others.

// 📌 Difference From Shallow Copy
// Shallow Copy:

// Copies pointer address

// All objects share same memory

// Changing one affects all

// Risk of double delete

// Deep Copy:

// Copies the actual data

// Memory allocated separately for each copy

// Safe & independent objects

// No shared memory problems

// ✔ Output Summary
// Obj1.value->data : 25
// Obj2.value->data : 0
// Obj3.value->data : 0