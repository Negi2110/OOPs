// ## ✅ What Is a Class Template? (Simple Meaning)

// > A **class template** allows you to create **generic classes** where the **data type is not fixed** — it is decided when the object is created.

// So instead of writing:

// ```cpp
// class IntBox { int data; };
// class FloatBox { float data; };
// ```

// You write **one class that works for all types** ✅

// ---

// ## ✅ Syntax (From Your Slide)

// ```cpp
// template <class T>
// class ClassName {
//     T data;     // T can be int, float, double, etc.
// };
// ```

// ✅ `class` and `typename` both mean the same here.

// ---

// ## ✅ Fully Commented Class Template Example

#include <iostream>
using namespace std;

/*
====================================================
CLASS TEMPLATE
====================================================
- T is a GENERIC TYPE
- This class can store ANY data type
*/

template <typename T>
class Box {
private:
    T value;   // ✅ Member variable of generic type T

public:
    // ✅ Constructor takes generic type
    Box(T v) : value(v) {}

    // ✅ Member function also uses generic type
    T getValue() {
        return value;
    }
};

int main() {

    // ✅ Box specialized for int
    Box<int> intBox(10);
    cout << intBox.getValue() << endl;

    // ✅ Box specialized for float
    Box<float> floatBox(3.14f);
    cout << floatBox.getValue() << endl;

    // ✅ Box specialized for string
    Box<string> stringBox("Hello");
    cout << stringBox.getValue() << endl;

    return 0;
}



// ## ✅ What Actually Happens Internally (Important Interview Insight)

// The compiler generates **three different classes**:

// ```cpp
// class Box<int> { ... };
// class Box<float> { ... };
// class Box<string> { ... };
// ```

// This again is:

// > ✅ **Compile-time polymorphism**

// ---

// ## ✅ Why Class Templates Are Powerful

// * ✅ Avoid writing the same class multiple times
// * ✅ Type safe (no casting)
// * ✅ No runtime overhead like virtual functions
// * ✅ Used heavily in STL:

//   * `std::vector<T>`
//   * `std::map<K, V>`
//   * `std::stack<T>`

// ---

// ## ✅ Template Class vs Normal Class

// | Feature               | Normal Class | Template Class       |
// | --------------------- | ------------ | -------------------- |
// | Works with one type   | ✅ Yes        | ❌ No                 |
// | Works with many types | ❌ No         | ✅ Yes                |
// | Type decided at       | Compile time | Object creation time |
// | Code duplication      | High         | Low                  |

// ---

// ## 🔥 One-Line Interview Finisher

// > “A class template allows defining a generic class where the data type is specified at object creation time, enabling code reuse without runtime overhead.”

// ---
