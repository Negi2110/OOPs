
// # ✅ **Assertions — Explained Clearly**

// An **assertion** in C++ is a **preprocessor macro** (not a function) that checks whether a condition is true at runtime. It is used mainly for **debugging**, not for error handling in production.

// ### ✔ If the condition is TRUE

// → The program continues normally.

// ### ❌ If the condition is FALSE

// → The program **prints an error message** showing:

// * The failed expression
// * The file name
// * The line number
//   And then **terminates the program** immediately.

// Assertions help you catch programming logic errors early while developing.

// ### ✔ Syntax

// ```cpp
// assert(condition);
// ```

// ### ✔ Header required:

// ```cpp
// #include <cassert>   // modern
// // or
// #include <assert.h>  // old style
// ```

// ### ✔ Condition must evaluate to an integer

// * 0 → false
// * Non-zero → true

// ---

// # ✅ **Fully Commented Example**

// ```cpp
#include <iostream>
#include <cassert>    // Needed for assert()
using namespace std;

int main() {

    int x;
    cout << "Enter a positive number: ";
    cin >> x;

    /*
        assert(x > 0);

        If x <= 0:
         - Assertion fails
         - Program stops
         - Error message shows:
             - failed condition: x > 0
             - file name
             - line number
    */
    assert(x > 0);

    cout << "Program continues because assertion passed!" << endl;

    return 0;
}
// ```

// ---

// # ✅ **Typical Output When Assertion Fails**

// ```
// Assertion failed: x > 0, file main.cpp, line 14
// ```

// ---

// # 🔥 **Very Important Notes (for exams + interviews)**

// * Assertions are used **during development**, not for user error handling.
// * Assertions **are removed** when you compile with `-DNDEBUG`, meaning no runtime checks.
// * They should **never** be used for validating user input or runtime errors.

// ---

// # 📝 **One-line Interview Answer**

// > “Assertions are debugging tools that stop the program if a condition is false, printing the file, line number, and failed expression.”

// ---
