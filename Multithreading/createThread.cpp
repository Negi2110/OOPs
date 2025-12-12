// ============================================================================
//  TOPIC: Types of Thread Creation in C++11
// ============================================================================
//
//  In modern C++ (C++11 and above), a thread can be created using 5 different 
//  types of callable objects. A *callable object* is anything that can be 
//  invoked using operator().
//
//  These 5 thread creation methods are:
//
//      1. Function Pointer
//      2. Function Object (Functor)
//      3. Lambda Expression
//      4. Member Function of a Class
//      5. Static Member Function of a Class
//
// -----------------------------------------------------------------------------
//  NOTE:
//  --------
//  When multiple threads are launched at the same time, the C++ runtime does 
//  NOT guarantee which thread will start executing first. Thread scheduling 
//  is handled by the operating system, not by your program.
// -----------------------------------------------------------------------------
//
//  1. Function Pointer
//     ----------------
//     This is the most basic form of thread creation where a plain C/C++
//     function (global or static) is passed as a callable to std::thread.
// ============================================================================
// #include <iostream>
// #include <thread>
// using namespace std;
// void fun(int x) {
//     while(x --> 0) {
//         cout << "Function Pointer Thread: " << x << endl;
//     }   
// }

// int main() {
//     std::thread t(fun,10);
//     std::thread t2(fun,10);
//     t.join();
//     t2.join();
//     cout << "Main Thread Finished" << endl;
//     return 0;
// }

//lambda function
/*
    The keyword `auto` in C++ is used for automatic type deduction. This means
    the compiler determines the variable's type based on the value assigned to it.
    In modern C++ (C++11 and above), `auto` is especially useful when working with 
    lambda expressions, because lambdas have unique compiler-generated types that 
    cannot be written manually in code. Therefore, when we write 
        auto fun = [](int x){ ... };
    the compiler automatically deduces the correct (hidden) lambda type. 
    Using `auto` makes the code cleaner, reduces redundancy, and is required when 
    storing lambda functions in variables. Overall, `auto` allows the compiler to 
    infer complex or unknown types while keeping the code simple and readable.
*/

// #include <iostream>
// #include <thread>
// using namespace std;
// int main() {
//     // auto fun = [](int x) {
//     //     while (x --> 0)
//     //     {
//     //         cout << "Lambda Function Thread: " << x << endl;
//     //     }

//     // };  
//     // std::thread t(fun, 10);
//     // std::thread t2(fun, 10);
//     // t.join();
//     // t2.join();
//     //we can directly pass lambda to thread without storing in variable
//     std::thread t([](int x) {
//         while (x --> 0)
//         {
//             cout << "Lambda Function Thread: " << x << endl;
//         }

//     }, 10);
//     t.join();
//     cout << "Main Thread Finished" << endl;
//     return 0;
// }


// //3.Functor (Function Object)
// #include <iostream>
// #include <thread> 
// class Base{
//     public:
//     void operator()(int x){
//         while (x --> 0)
//         {
//             std::cout << "Functor Thread: " << x << std::endl;
//         }
//     }
// };
// int main() {
//     std::thread t(Base(), 10); // Create thread with Functor
//     t.join();
//     std::cout << "Main Thread Finished" << std::endl;
//     return 0;
// }


/*
    =====================================================================================
    🔹 HOW THREAD WITH A FUNCTOR WORKS IN C++ (INTERVIEW EXPLANATION)
    =====================================================================================

    A *functor* (also called a "function object") is a class that overloads the 
    function-call operator:  operator(). 

    This makes objects of the class behave like a function.

    -------------------------------------------------------------------------------------
    🔸 1. Understanding the Functor Class
    -------------------------------------------------------------------------------------

        class Base {
        public:
            void operator()(int x) {
                while (x --> 0) {
                    std::cout << "Functor Thread: " << x << std::endl;
                }
            }
        };

    • The class `Base` overloads operator(), so an object of `Base` can be "called" 
      like a function.

            Base b;
            b(10);     // This calls operator()(10)

    • This allows the object to be used anywhere a callable is required, including 
      std::thread.

    • Inside `operator()`, the loop runs until x decreases to 0 and prints a message 
      each time — this becomes the thread's task.

    -------------------------------------------------------------------------------------
    🔸 2. How std::thread Uses the Functor
    -------------------------------------------------------------------------------------

        std::thread t(Base(), 10);

    • Here, `Base()` creates a temporary functor object.
    • `std::thread` looks for something callable — a function, lambda, or functor.
    • It treats the functor exactly like a function:

            Base()(10);

    • The thread constructor internally calls:

            Base tempObject;
            tempObject.operator()(10);

    • This call runs in a *separate thread*, independent of main.

    -------------------------------------------------------------------------------------
    🔸 3. Why Functors Are Used in Multithreading
    -------------------------------------------------------------------------------------

    ✔ They allow storing state inside the object.  
      (You can add member variables that the thread will use.)

    ✔ They make code more organized compared to global functions.

    ✔ They behave like a callable function but can still hold data, unlike a normal 
      function pointer.

    ✔ They are faster than std::function and easy for compilers to optimize.

    -------------------------------------------------------------------------------------
    🔸 4. Why We Call join()
    -------------------------------------------------------------------------------------

        t.join();

    • join() blocks the main thread until the functor thread finishes its work.
    • Without join(), the main thread may finish earlier, causing std::terminate().

    -------------------------------------------------------------------------------------
    🔸 Final Summary (Interview Point)
    -------------------------------------------------------------------------------------

    A functor is a class with operator() overloaded so its objects behave like 
    functions. In C++, std::thread can accept any callable object — function pointer, 
    lambda, or functor. When we pass a functor to std::thread, the thread calls the 
    overloaded operator() in a separate execution flow. Functors are powerful because 
    they allow threads to run behavior that is encapsulated inside a class object.
*/


// //4.Non-Static Member Function
// #include <iostream>
// #include <thread>
// using namespace std;
// class Base {
//   public:
//      void run(int x) {
//         while(x-->0) {
//             cout << "Non-Static Member Function Thread: " << x << endl;
//         }
//      }
//      void run1(int x) {
//         while(x-->0) {
//             cout << "Non-Static Member Function Thread 1: " << x << endl;
//         }
//      }
// };
// int main() {
//     Base b;
//     std::thread t(&Base::run, &b, 10); // Create thread with Non-Static Member Function
//     std::thread t1(&Base::run1, &b, 10); // Create another thread with Non-Static Member Function
//     t.join();
//     t1.join();
//     cout << "Main Thread Finished" << endl;
//     return 0;   
// }

// A non-static member function needs an object instance because it uses the this pointer.
// But different threads may use the same object OR different objects.
// The object does not have to be the same — it only has to be an instance of the class.
/*
    =====================================================================================
    🔹 THREAD WITH NON-STATIC MEMBER FUNCTION — INTERVIEW EXPLANATION
    =====================================================================================

    In C++, std::thread can execute not only free functions, lambdas, and functors,
    but also **non-static member functions**. However, there is a key difference:
    a non-static member function always needs an **object** to run on, because it
    implicitly requires a `this` pointer.

    -------------------------------------------------------------------------------------
    🔸 Why non-static member functions need special syntax?
    -------------------------------------------------------------------------------------
    A normal function pointer looks like:
        void (*fp)(int);

    But a member function pointer looks like:
        void (Base::*fp)(int);

    Because non-static member functions need to know *which object* they will operate on.

    -------------------------------------------------------------------------------------
    🔸 Thread syntax for non-static member functions
    -------------------------------------------------------------------------------------
        std::thread t(&Base::run, &b, 10);

    Explanation:
    • &Base::run  → Pointer to member function (not callable alone)
    • &b          → Address of the object whose run() function should execute
    • 10          → Argument passed to run(int x)

    Internally, the thread executes:
        (b.*&Base::run)(10);

    In simple words:
        → "Call b.run(10) inside a new thread."

    This is one of the most common interview questions because the syntax looks unusual.

    -------------------------------------------------------------------------------------
    🔸 Why can't we pass run() directly like a normal function?
    -------------------------------------------------------------------------------------
    Because run() is a **non-static** member function:
    • It requires a `this` pointer.
    • It belongs to an object, not to the class itself.
    • It cannot be invoked without specifying which object to run on.

    Hence we must pass BOTH:
        1. The member function pointer (&Base::run)
        2. The object (&b)

    -------------------------------------------------------------------------------------
    🔸 Key difference: Static vs Non-Static member functions
    -------------------------------------------------------------------------------------
    STATIC MEMBER FUNCTION:
        • Does NOT require an object
        • Does NOT use `this`
        • Can be passed to thread just like normal functions:
              std::thread t(Base::run, 10);

    NON-STATIC MEMBER FUNCTION:
        • Requires object instance
        • Uses `this` pointer internally
        • Must be passed using:
              std::thread t(&Base::run, &object, args);

    -------------------------------------------------------------------------------------
    🔸 What happens when thread starts?
    -------------------------------------------------------------------------------------
    The thread executes:
        b.run(10);

    while the main thread continues until `t.join()` forces it to wait.

    -------------------------------------------------------------------------------------
    🔸 Why do we call join()?
    -------------------------------------------------------------------------------------
    • join() blocks the main thread until the worker thread completes.
    • Without join(), the program may terminate early and kill the thread.
    • This prevents runtime errors and ensures proper thread cleanup.

    -------------------------------------------------------------------------------------
    🔸 Interview Summary (Use This)
    -------------------------------------------------------------------------------------
    • A non-static member function requires an object, so we pass BOTH 
      `&Class::Function` and the object pointer to std::thread.
    • std::thread invokes it using the object’s `this` pointer internally.
    • This is different from static member functions which behave like normal functions.
    • The typical syntax is:
            std::thread t(&Class::method, &object, args...);
    • Understanding this syntax is a common C++ interview requirement because it tests 
      your knowledge of pointers-to-member-functions and thread creation rules.

*/


// ============================================================================
// 5. Static Member Function Thread  (Interview Explanation + Code)
// ============================================================================

#include <iostream>
#include <thread>
using namespace std;

// -----------------------------------------------------------------------------
// CLASS WITH A STATIC MEMBER FUNCTION
// -----------------------------------------------------------------------------
class Base
{
public:
    // Static member function
    // NOTE: Static functions do NOT belong to any object, so they:
    //       ✔ do NOT have a 'this' pointer
    //       ✔ do NOT require an object to call them
    //       ✔ behave like normal C functions
    static void run(int x) 
    {
        // Simple loop to show this function runs inside a thread
        while (x-- > 0) {
            cout << "Static Function Thread: " << x << endl;
        }
    }
};


// -----------------------------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------------------------
int main() 
{
    // Creating a thread using a static member function
    // IMPORTANT (Interview Point):
    // Since run() is static:
    //    ✔ We pass it just like a normal function pointer
    //    ✔ No object instance is required
    // Thread executes: Base::run(10)
    std::thread t(&Base::run, 10);

    // Wait for thread to finish (blocks main thread)
    t.join();

    cout << "Main Thread Finished" << endl;
    return 0;
}
// ```

// ---

// # ✅ **Interview Points Covered by This Code**

// ### ✔ Static member functions behave like normal C functions

// * No object required
// * No `this` pointer
// * Can be passed directly to `std::thread`

// ### ✔ Thread creation syntax is simpler than non-static functions

// Non-static needs:

// ```cpp
// std::thread t(&Base::run, &object, args);
// ```

// Static only needs:

// ```cpp
// std::thread t(Base::run, args);
// ```

// ### ✔ Thread uses the static function as the thread entry point

// It runs independently without any class instance.

// ---
// ============================================================================
// END OF TOPIC
// ============================================================================