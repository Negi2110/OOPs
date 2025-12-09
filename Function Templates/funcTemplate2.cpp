
#include <iostream>
using namespace std;

/*
====================================================
FUNCTION TEMPLATE WITH TWO DIFFERENT TYPES
====================================================
- T  → type of first parameter
- U  → type of second parameter
- Return type is T  ⚠ (IMPORTANT!)
*/

template <typename T, typename U>
T GetMin(T a, U b) {

    // ✅ Variable of return type T
    T result;

    // ✅ Comparison between T and U is allowed if operator < exists
    // ⚠ If b is smaller and U is larger than T can store, data LOSS may happen
    result = (a < b) ? a : b;

    // ✅ Always returns type T (even if b was chosen)
    return result;
}

int main() {

    // ✅ Two different types
    int i = 10;     // T will be int
    long l = 99;    // U will be long

    /*
    ====================================================
    EXPLICIT TEMPLATE INSTANTIATION
    ====================================================
    We are explicitly telling the compiler:
    T = int
    U = long
    */

    cout << GetMin<int, long>(i, l) << endl;

    /*
    Internally the compiler generates this function:

    int GetMin(int a, long b) {
        int result;
        result = (a < b) ? a : b;
        return result;
    }

    Since 10 < 99 → result = 10 → returned as int ✅ safe
    */

    return 0;
}
// ```

// ---

// ## ✅ What This Example Demonstrates (Interview Gold)

// * ✅ **Multiple template types**:

//   ```cpp
//   template <typename T, typename U>
//   ```
// * ✅ You can mix **different data types**:

//   ```cpp
//   GetMin<int, long>(i, l);
//   ```
// * ✅ The compiler generates a **real function at compile time**
// * ✅ The return type is **fixed as `T`**
// * ⚠ This can cause **data loss** in some cases

// ---

// ## ⚠ IMPORTANT Hidden Danger in This Design

// If you did this:

// ```cpp
// int i = 1000000000;
// long l = 2000000000;

// cout << GetMin<int, long>(i, l);
// ```

// Still fine ✅
// But if reversed:

// ```cpp
// cout << GetMin<int, long>(2000000000, -5L);
// ```

// * `b = -5` is `long`
// * It will return `b`
// * But return type is **int**
// * ⚠ **Narrowing conversion + possible overflow**

// ---

// ## ✅ Safer Modern Version (Interview Bonus)

// ```cpp
// template <typename T, typename U>
// auto GetMinSafe(T a, U b) {
//     return (a < b) ? a : b;   // return type auto-deduced safely
// }
// ```

// ---

// ## 🔥 One-Line Interview Finisher

// > “This example shows a function template with two different type parameters, where `T` defines the return type, allowing mixed-type comparisons but requiring care to avoid unsafe narrowing conversions.”

