#include <iostream>     // For input and output
#include <exception>   // For std::exception base class
using namespace std;

/*
    Custom exception class for memory-related errors.
    This class inherits from std::exception.
*/
class MemoryException : public std::exception {
public:
    /*
        what() is a virtual function from std::exception.
        It is overridden here to return a custom error message.
        const  -> function will not modify the object
        noexcept -> function will not throw another exception
    */
    const char* what() const noexcept override {
        return "My exception happened";
    }
};

int main() {

    char* buffer = nullptr;   // Pointer to store dynamically allocated memory
    int size;                 // Variable to store the array size entered by user

    // Creating an object of our custom exception class
    MemoryException me;

    try {
        // Asking the user for array size
        cout << "Enter array size: ";
        cin >> size;

        /*
            Dynamically allocating memory for character array.
            In modern C++, if memory allocation fails,
            new automatically throws std::bad_alloc.
        */
        buffer = new char[size];

        /*
            Old-style NULL check.
            In modern C++, this block usually won't run
            because std::bad_alloc is thrown automatically.
        */
        if (buffer == nullptr)
            throw me;   // Throwing our custom exception object
    }

    /*
        Catching the exception BY VALUE as shown in the slide.
        (Note: Best practice is to catch by const reference)
    */
    catch (MemoryException e) {
        // Displaying the exception message using what()
        cout << "Exception: " << e.what() << endl;
    }

    // Freeing allocated memory to avoid memory leak
    delete[] buffer;

    return 0;
}
// ```

// ---

// ## ✅ **What This Example Demonstrates**

// * How to **create a custom exception class**
// * How to **override the `what()` function**
// * How to **throw a user-defined exception object**
// * How to **catch and display the error message**
// * How to **dynamically allocate memory using `new`**
// * How to safely **free memory using `delete[]`**

// ---

// ## ✅ **Important Interview Corrections vs Slide Code**

// | Slide Code                 | Modern Best Practice                |
// | -------------------------- | ----------------------------------- |
// | `catch(MemoryException e)` | `catch(const MemoryException& e)` ✅ |
// | `if (buffer == 0)`         | `new` throws `std::bad_alloc` ✅     |
// | `throw()` in `what()`      | `noexcept` ✅                        |

