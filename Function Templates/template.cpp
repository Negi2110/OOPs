
#include <iostream>
using namespace std;

/*
====================================================
FUNCTION TEMPLATE: GetMax
====================================================
- template <typename T> means:
  ✅ T is a GENERIC TYPE (can be int, float, char, etc.)
- The compiler will create a SEPARATE real function
  for each type that is used.
*/

template <typename T>
T GetMax(T a, T b) {

    // ✅ Variable of generic type T
    T result;

    // ✅ T must support the '>' operator
    result = (a > b) ? a : b;

    // ✅ Return the greater value
    return result;
}

int main() {

    /*
    ====================================================
    EXPLICIT TEMPLATE INSTANTIATION
    ====================================================
    Here we are explicitly telling the compiler:
    👉 "Create an int version of GetMax"
    */

    cout << GetMax<int>(14, 8) << endl;
    // Internally becomes:
    // int GetMax(int a, int b)

    /*
    ====================================================
    FLOAT VERSION
    ====================================================
    Compiler generates:
    float GetMax(float a, float b)
    */

    cout << GetMax<float>(1.5, 2.75) << endl;

    /*
    ====================================================
    CHAR VERSION
    ====================================================
    Characters are compared using ASCII values:
    'M' = 77, 'C' = 67
    So result will be 'M'
    */

    cout << GetMax<char>('M', 'C') << endl;

    return 0;
}
// ## ✅ What This Program Proves (Important Interview Points)

// * ✅ **One single function works for many data types**
// * ✅ The compiler generates:

//   * `GetMax<int>`
//   * `GetMax<float>`
//   * `GetMax<char>`
// * ✅ This is called:

//   > **Compile-time polymorphism**
// * ✅ No runtime overhead like virtual functions
// * ✅ Type safety is fully enforced by the compiler

// ---

// ## ✅ Implicit vs Explicit Template Calls (Extra Interview Tip)

// You wrote:

// ```cpp
// GetMax<int>(14, 8);
// ```

// You could also write:

// ```cpp
// GetMax(14, 8);     // Compiler auto-detects int
// GetMax(1.5, 2.75); // Compiler auto-detects double
// ```

// This is called **template type deduction**.

// ---

// ## 🔥 One-Line Interview Finisher

// > “This program shows how a single function template generates multiple type-specific functions at compile time for `int`, `float`, and `char`, avoiding code duplication and runtime overhead.”
