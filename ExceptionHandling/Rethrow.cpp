#include <iostream>
#include <exception>
using namespace std;

/*
    GeneralException: a simple custom exception derived from std::exception.
    It carries a message and overrides what().
*/
class GeneralException : public std::exception {
    string msg;
public:
    explicit GeneralException(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

/*
    AnotherExceptionExample demonstrates:
    - throwing an exception
    - catching it locally (for logging/cleanup)
    - re-throwing the same exception to be handled by a higher-level caller
*/
class AnotherExceptionExample {
private:
    GeneralException generalError{ "General failure in DoSomething()" };

public:
    // DoSomething may throw GeneralException
    void DoSomething() /* modern code: use noexcept only if guaranteed */ {
        try {
            // simulate an error condition by throwing the member exception object
            throw generalError;          // throw original exception (by value)
        }
        catch (const GeneralException& e) {
            // Local handling: logging / partial handling
            cout << "Inner handler: Logged -> " << e.what() << endl;

            // Re-throw the *same* exception object to let higher-level handlers decide
            // Use plain 'throw;' to propagate the currently handled exception without copying.
            throw;
        }
    }

    // Controller function calls DoSomething and handles propagated exceptions
    void Controller() {
        try {
            DoSomething();
        }
        catch (const GeneralException& e) {
            // Final handling of the re-thrown exception
            cout << "Outer handler: Final handling -> " << e.what() << endl;
        }
    }
};

int main() {
    AnotherExceptionExample ex;

    // Run controller which demonstrates inner catch + rethrow + outer catch
    ex.Controller();

    return 0;
}


// What this does (expected output):

// ```
// Inner handler: Logged -> General failure in DoSomething()
// Outer handler: Final handling -> General failure in DoSomething()
// ```

// Key interview points shown here:

// * Use `catch(const T&)` to avoid copies and slicing.
// * Use `throw;` (no operand) inside a `catch` to re-throw the same exception object.
// * Do local work (logging/cleanup) in the inner `catch`, then let a higher-level handler decide final recovery.
