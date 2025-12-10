#include <iostream>
using namespace std;

int main() {

    char* buffer = nullptr;   // Pointer to dynamically allocated character array
    int size;                 // Variable to store user input for array size

    try {
        // Ask the user to enter the array size
        cout << "Enter array size: ";
        cin >> size;

        // If the size is invalid (less than 1), throw an integer exception
        if (size < 1)
            throw 1;   // Throwing an int type exception

        // Try to dynamically allocate memory for the character array
        buffer = new char[size];   // Memory allocation

        // If memory allocation fails, buffer becomes NULL (old compilers)
        // In modern C++, new throws std::bad_alloc automatically
        if (buffer == nullptr)
            throw "Out of Memory";   // Throwing a string literal exception

        // If everything works fine
        cout << "Memory allocated successfully!" << endl;
    }

    // This catch block handles string-type exceptions (char*)
    catch (char* error) {
        cout << "Exception: " << error << endl;
    }

    // This catch block handles integer-type exceptions
    catch (int errorNo) {
        cout << "Exception: Invalid array size (" << errorNo << ")" << endl;
    }

    // This catch block handles any unknown exception type
    catch (...) {
        cout << "Exception: Unknown error occurred" << endl;
    }

    // Free the allocated memory to avoid memory leaks
    delete[] buffer;

    return 0;
}
// ```

// ---

// ## ✅ What this program demonstrates (in interview language):

// * `throw 1;` → Throws an **integer exception** when size is invalid
// * `throw "Out of Memory";` → Throws a **string exception** for memory failure
// * `catch(char*)` → Catches string-based errors
// * `catch(int)` → Catches numeric errors
// * `catch(...)` → Catches **any unknown exception**
// * Only the **matching catch block executes**
// * Memory is released using `delete[]` to avoid **memory leaks**

// ---

// ## ✅ One-Line Interview Summary:

// > “This program shows chained exception handlers where different exception types are caught by matching `catch` blocks, with `catch(...)` acting as a safety fallback.”

// A string literal thrown using throw "error"; is caught by catch(const char*), not by catch(int) or catch(...).