
// ## ✅ **Re-throwing an Exception – Simple Explanation**

// Sometimes an exception is **caught for logging, cleanup, or partial handling**, but the program is **not ready to fully handle it at that level**. In that case, the same exception is **thrown again to a higher-level handler** — this is called **re-throwing an exception**. This is done using **just `throw;` inside a `catch` block**, without writing the exception object again. The re-thrown exception is then caught by an outer `catch` block. It is important to ensure that **some higher-level handler exists**, otherwise the program will terminate.

// ---

// ## ✅ **Fully Commented Example: Re-throwing an Exception**

// ```cpp
#include <iostream>
#include <exception>
using namespace std;

/*
    Custom exception class derived from std::exception
*/
class MyException : public std::exception {
public:
    // Overriding what() to return an error message
    const char* what() const noexcept override {
        return "Critical System Failure!";
    }
};

int main() {

    try {
        try {
            // Throwing a custom exception
            throw MyException();
        }

        /*
            First catch block:
            - Catches the exception
            - Performs partial handling (like logging)
            - Then RE-THROWS the SAME exception upward
        */
        catch (const MyException& e) {
            cout << "Inner Catch: Logging Error -> " << e.what() << endl;

            throw;   // ✅ Re-throwing the SAME exception
        }
    }

    /*
        Outer catch block:
        - Receives the re-thrown exception
        - Performs final handling
    */
    catch (const MyException& e) {
        cout << "Outer Catch: Final Handling -> " << e.what() << endl;
    }

    return 0;
}
// ```

// ---

// ## ✅ **Output**

// ```
// Inner Catch: Logging Error -> Critical System Failure!
// Outer Catch: Final Handling -> Critical System Failure!
// ```

// ---

// ## ✅ **Key Rules for Re-throwing (Very Important for Interview)**

// * ✅ Use **`throw;` only inside a `catch` block**
// * ✅ Do **NOT write `throw e;`** (it creates a copy)
// * ✅ The **same original exception object is propagated**
// * ✅ There **must be another handler above**
// * ✅ Used for:

//   * Logging
//   * Cleanup
//   * Resource release
//   * Multi-layer error handling

// ---

// ## ✅ **One-Line Interview Answer**

// > “Re-throwing an exception means propagating the same caught exception to a higher-level handler using `throw;` without specifying the object again.”

// ---
