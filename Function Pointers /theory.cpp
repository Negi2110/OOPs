// Perfect — here’s **one compact, single C++ program that demonstrates all four together**:

// ✅ Function pointers vs `std::function`
// ✅ Callbacks using function pointers
// ✅ Array of function pointers
// ✅ `typedef` / `using` for clean syntax

// All explained with **tight comments inside the code** 👇

// ---

// ```cpp
#include <iostream>
#include <functional>   // For std::function
using namespace std;

/*
====================================================
1️⃣ NORMAL FUNCTIONS (WILL BE USED EVERYWHERE)
====================================================
*/

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

/*
====================================================
2️⃣ FUNCTION POINTER TYPEDEF (CLEAN SYNTAX)
====================================================
Instead of writing:
    int (*ptr)(int, int);
We write:
*/

using MathFunc = int (*)(int, int);   // ✅ typedef for function pointer


/*
====================================================
3️⃣ CALLBACK FUNCTION USING FUNCTION POINTER
====================================================
- This function accepts a FUNCTION POINTER as a callback
- Then it calls that function internally
*/

void executeCallback(MathFunc callback, int x, int y) {
    // ✅ Calling the passed function (callback)
    cout << "Callback result = " << callback(x, y) << endl;
}


/*
====================================================
MAIN FUNCTION
====================================================
*/

int main() {

    /*
    ============================================
    ✅ FUNCTION POINTER vs std::function
    ============================================
    */

    // ✅ Raw function pointer (fast, low-level)
    MathFunc fp = add;
    cout << "Function Pointer Result = " << fp(10, 5) << endl;

    // ✅ std::function (can store functions, lambdas, functors)
    function<int(int, int)> sf = add;
    cout << "std::function Result = " << sf(10, 5) << endl;

    // ✅ std::function storing a lambda (IMPOSSIBLE with raw function pointer)
    function<int(int, int)> lambdaFunc = [](int a, int b) {
        return a * b;
    };
    cout << "Lambda via std::function = " << lambdaFunc(10, 5) << endl;


    /*
    ============================================
    ✅ FUNCTION POINTER AS CALLBACK
    ============================================
    */

    executeCallback(add, 20, 10);   // ✅ Calls add inside executeCallback
    executeCallback(sub, 20, 10);   // ✅ Calls sub inside executeCallback


    /*
    ============================================
    ✅ ARRAY OF FUNCTION POINTERS (JUMP TABLE)
    ============================================
    */

    MathFunc operations[2];   // ✅ Array of function pointers

    operations[0] = add;
    operations[1] = sub;

    int x = 50, y = 30;

    cout << "Array[0] Add = " << operations[0](x, y) << endl;
    cout << "Array[1] Sub = " << operations[1](x, y) << endl;


    /*
    ============================================
    ✅ WHY std::function IS DIFFERENT
    ============================================
    */

    int factor = 3;

    // ❌ This CANNOT be stored in a raw function pointer:
    // int (*badPtr)(int,int) = [factor](int a,int b){ return (a+b)*factor; };

    // ✅ But std::function CAN store this (stateful lambda)
    function<int(int, int)> statefulLambda =
        [factor](int a, int b) {
            return (a + b) * factor;
        };

    cout << "Stateful lambda via std::function = "
         << statefulLambda(10, 5) << endl;

    return 0;
}
// ```

// ---

// ## ✅ What This **Single Program** Demonstrates

// * ✅ **Function pointer** → fast, raw, low-level
// * ✅ **`std::function`** → flexible, stores lambdas & functors
// * ✅ **Callback** → passing function pointer into another function
// * ✅ **Array of function pointers** → runtime behavior switching (jump table)
// * ✅ **`using` typedef** → simplifies ugly pointer syntax

// ---

// ## 🔥 Ultra-Short Interview Wrap-Up

// > “Function pointers are fast and low-level, `std::function` is flexible and can store lambdas, callbacks allow functions to be passed and executed later, arrays of function pointers enable runtime behavior selection, and typedefs make all of this readable.”

// ---

