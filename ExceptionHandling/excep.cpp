// 1. ✅ A **clear explanation in simple words**
// 2. ✅ A **modern, corrected C++ version with full detailed comments** (best practice)

// ## ✅ **Explanation of the Slide (In Simple Words)**

// This example defines a **custom exception class `IOException` derived from `std::exception`** and overrides the `what()` function to return the message `"Controller Error"`. An object of this class is created and **thrown using `throw eio;`** inside the `try` block. The exception is then **caught using `catch(IOException& e)`**, meaning it is **caught by reference**, which avoids making a copy of the exception object and is more efficient. Inside the catch block, the program calls **`e.what()` to display the error message**. As a result, the output printed on the screen is:

// ```
// Controller Error
#include <iostream>
#include <exception>   // For std::exception
using namespace std;

/*
    Custom exception class derived from std::exception.
    It overrides what() to return a custom error message.
*/
class IOException : public std::exception {
public:
    // what() returns the error description
    const char* what() const noexcept override {
        return "Controller Error";
    }
};

int main() {

    try {
        IOException eio;   // Creating an exception object

        // Throwing the custom exception object
        throw eio;
    }

    // Catching the exception BY REFERENCE to avoid copying
    catch (const IOException& e) {
        // Accessing the error message using what()
        cout << e.what() << endl;
    }

    return 0;
}


// ## ✅ **Why Catch by Reference is Important**

// | Method                          | Effect                                       |
// | ------------------------------- | -------------------------------------------- |
// | `catch(IOException e)`          | Creates a **copy** of the exception (slower) |
// | `catch(const IOException& e)` ✅ | **No copy**, faster, safe, best practice     |

// ---

// ## ✅ **Key Interview Points**

// * Custom exceptions should **inherit from `std::exception`**
// * `what()` is used to fetch the **error message**
// * Exceptions should be **caught by `const&`**
// * This avoids **copy overhead and slicing**
// * The output will be:

//   ```
//   Controller Error
//   ```

// ---

// ## ✅ **One-Line Interview Answer**

// > “Catching exceptions by reference avoids unnecessary copying and allows safe access to the error message using `what()`.”

// ---

