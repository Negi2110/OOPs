// # ✅ **What is a Static Member Function?**

// A **static member function**:

// * belongs to the **class**, not to any object
// * does **NOT** have a `this` pointer
// * can be called without creating an object
// * behaves just like a normal C function

// Because there is **no `this`**, static member functions are extremely simple to use with threads.

// ---

// # ✅ **How Static Member Functions Work with Threads**

// Since they don’t need an object, you can directly pass them to `std::thread` like this:

// ```cpp
// class Base {
// public:
//     static void run(int x) {
//         while (x --> 0) {
//             std::cout << "Static Function Thread: " << x << std::endl;
//         }
//     }
// };

// int main() {
//     std::thread t(Base::run, 10);  // NO object needed
//     t.join();
// }
// ```

// ### ✔ No `&Base::run` needed

// ### ✔ No object (`&b`) needed

// ### ✔ No instance required

// The thread simply calls:

// ```
// Base::run(10)
// ```

// Just like a normal standalone function.

// ---

// # 🧠 **Static vs Non-Static in Threading — Interview Comparison**

// | Feature                | Static Member Function             | Non-Static Member Function                |
// | ---------------------- | ---------------------------------- | ----------------------------------------- |
// | Has `this` pointer?    | ❌ No                               | ✔ Yes                                     |
// | Requires an object?    | ❌ No                               | ✔ Yes (`&object`)                         |
// | How to pass to thread? | `std::thread t(Base::func, args);` | `std::thread t(&Base::func, &obj, args);` |
// | Thread-safety?         | Safer (no state)                   | Risky unless protected                    |
// | Supports shared data?  | Only static globals                | Object-level shared data                  |

// ---

// # 🔥 Key Interview Insight

// > **Static member functions behave like normal C functions.
// > They do not belong to any specific object and can be passed to threads directly.
// > Non-static member functions require an object instance because they use `this`.**

// This distinction is fundamental and often asked.

// ---

// # 🧪 Full Example: Both Static and Non-Static

// ```cpp
#include <iostream>
#include <thread>
using namespace std;

class Base {
public:
    static void staticRun(int x) {
        while (x --> 0) {
            cout << "Static Thread: " << x << endl;
        }
    }

    void nonStaticRun(int x) {
        while (x --> 0) {
            cout << "Non-Static Thread: " << x << endl;
        }
    }
};

int main() {
    Base b;

    std::thread t1(Base::staticRun, 5);      // static — no object needed
    std::thread t2(&Base::nonStaticRun, &b, 5); // non-static — object required

    t1.join();
    t2.join();
}
// ```

// ---

// # 🏆 Final Interview Summary (Use This)

// > **Static member functions do not require an object and act like normal functions.
// > They are easy to pass to threads because they do not depend on a `this` pointer.
// > Non-static member functions require both a member-function pointer and an object
// > because they implicitly use `this`.**

// ---

