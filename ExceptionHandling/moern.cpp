
#include <iostream>     // For input and output
#include <exception>   // For std::exception base class
using namespace std;

/*
    Custom exception class that stores extra information (error data).
    It inherits from std::exception.
*/
class MyException : public std::exception {
public:
    int data;   // Variable to store additional error information

    /*
        Constructor that receives error data.
        This allows us to pass extra information along with the exception.
    */
    MyException(int d) : data(d) { }

    /*
        Overriding what() function from std::exception.
        const     -> function does not modify object state
        noexcept  -> function guaranteed not to throw exception
    */
    const char* what() const noexcept override {
        return "My exception happened";
    }
};

int main() {

    // Creating an exception object with extra error information (100)
    MyException ex(100);

    try {
        // Throwing the custom exception object
        throw ex;
    }

    /*
        Catching the exception BY REFERENCE.
        This avoids copying and preserves the original object.
    */
    catch (const MyException& e) {

        // Displaying the main exception message using what()
        cout << e.what() << endl;

        // Displaying the additional error data passed via constructor
        cout << "Error Number: " << e.data << endl;
    }

    return 0;
}
// ```

// ---

// ## ✅ **Output of This Program**

// ```
// My exception happened
// Error Number: 100
// ```

// ---

// ## ✅ **What This Example Demonstrates**

// * ✅ How to **store extra information inside an exception object**
// * ✅ How to **pass data through the exception constructor**
// * ✅ How to **override `what()`**
// * ✅ How to **catch exceptions by reference**
// * ✅ How to **access both standard message and custom data**
// * ✅ How professional systems attach **error codes** to exceptions

// ---

// ## ✅ **One-Line Interview Answer**

// > “Extra information can be passed to an exception using its constructor and later accessed inside the catch block through the exception object.”

// ---

// ## ✅ **Why This Is Very Important in Real Projects**

// This pattern is used in:

// * ✅ Operating systems
// * ✅ Game engines
// * ✅ Defense simulations
// * ✅ Network servers
// * ✅ Database engines

// Because errors always need:
// ✔ A **message**
// ✔ A **numeric error code**
// ✔ Sometimes **file/line/module info**

