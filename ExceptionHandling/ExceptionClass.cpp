
// ## ✅ **Exception Class – Explained Clearly**

// In C++, although **any user-defined type can be thrown as an exception**, the C++ Standard Library provides a **base class called `std::exception`** in the `<exception>` header inside the `std` namespace. This base class contains a **single virtual member function `what()`**, which returns a `const char*` message describing the error. By **deriving your own exception class from `std::exception` and overriding the `what()` function**, you can provide meaningful, human-readable error messages. The `const` after `what()` means that this function **does not modify the object’s state**, and in modern C++ it is also marked `noexcept` to guarantee that it does not throw further exceptions.

// ---

// ## ✅ **Correct Modern Version of the Code from the Slide**

// ```cpp
#include <iostream>
#include <exception>   // For std::exception
using namespace std;

/*
    Custom exception class derived from std::exception.
    It overrides the what() function to return a custom message.
*/
class MyException : public std::exception {
public:
    // what() returns a constant C-string describing the error
    const char* what() const noexcept override {
        return "My exception happened";
    }
};

int main() {
    try {
        // Throwing a user-defined exception object
        throw MyException();
    }
    catch (const MyException& e) {   // Catching by reference (best practice)
        cout << "Caught Exception: " << e.what() << endl;
    }

    return 0;
}
// ```

// ---

// ## ✅ **Key Points for Interview**

// * `std::exception` is the **base class for all standard exceptions**
// * `what()` is a **virtual function** used to retrieve the error message
// * Custom exceptions **should always inherit from `std::exception`**
// * `const` after `what()` → function does **not modify the object**
// * `noexcept` after `what()` → function will **not throw another exception**
// * Always catch exceptions using **`const &`**

// ---

// ## ✅ **One-Line Interview Answer**

// > “In C++, custom exception classes are derived from `std::exception` and override the virtual `what()` function to provide meaningful error messages.”

// ---
