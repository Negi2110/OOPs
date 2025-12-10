
#include <iostream>
#include <exception>   // For std::exception
#include <new>         // For std::bad_alloc
using namespace std;

/*
    Custom exception class derived from std::exception.
    This allows us to return custom error messages using what().
*/
class InvalidSizeException : public std::exception {
public:
    // Overriding what() to return our custom error message
    const char* what() const noexcept override {
        return "Invalid array size! Size must be greater than zero.";
    }
};

int main() {

    char* buffer = nullptr;   // Pointer for dynamic memory
    int size;                 // Variable to store array size

    try {
        // Ask the user for array size
        cout << "Enter array size: ";
        cin >> size;

        // If size is invalid, throw a custom exception object
        if (size < 1)
            throw InvalidSizeException();  // ✅ Modern custom exception

        /*
            Attempt to allocate memory dynamically.
            If allocation fails, C++ automatically throws std::bad_alloc
        */
        buffer = new char[size];

        cout << "Memory allocated successfully!" << endl;
    }

    // ✅ Catches memory allocation failure (new failure)
    catch (const std::bad_alloc& e) {
        cout << "Memory Allocation Failed: " << e.what() << endl;
    }

    // ✅ Catches our custom invalid size exception
    catch (const InvalidSizeException& e) {
        cout << "Invalid Size Error: " << e.what() << endl;
    }

    // ✅ Catches any standard exception
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }

    // ✅ Final safety net for non-standard exceptions
    catch (...) {
        cout << "Unknown Exception Occurred!" << endl;
    }

    // Free allocated memory safely
    delete[] buffer;

    return 0;
}
// ```

// ---

// ## ✅ **What This Modern Program Demonstrates**

// | Feature                | Explanation                                |
// | ---------------------- | ------------------------------------------ |
// | `std::exception`       | Base class for all modern C++ exceptions   |
// | `what()`               | Returns human-readable error message       |
// | `std::bad_alloc`       | Automatically thrown when `new` fails      |
// | Custom exception class | For user-defined errors                    |
// | `const &` in catch     | Prevents unnecessary copying               |
// | `noexcept`             | Guarantees no crash during error reporting |

// ---

// ## ✅ **Why This Is Better Than Old `throw int` / `throw char*`**

// | Old Style        | Modern Style                       |
// | ---------------- | ---------------------------------- |
// | `throw 1;`       | `throw CustomException();`         |
// | `throw "error";` | `throw std::runtime_error("msg");` |
// | Unsafe           | Fully safe                         |
// | No hierarchy     | Full exception hierarchy           |
// | Weak debugging   | Strong debugging                   |

// ---

// ## ✅ **One-Line Interview Answer**

// > “In modern C++, exceptions should be derived from `std::exception` and caught by `const std::exception&` for safety, clarity, and compatibility with standard error handling.”

// ---
