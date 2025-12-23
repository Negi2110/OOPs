#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

static int s = 0;   // ❓ Is this thread-safe?

void fun() {
    int count = 100000;
    while (count--) {
        ++s;       // ❌ Data race here
    }
    cout << s << endl;
}

int main() {
    thread t1(fun);
    thread t2(fun);

    t1.join();
    t2.join();
}
// ```

// ---

// ## Why `static` Is NOT Thread-Safe

// ### 🔹 What `static int s = 0;` means

// * `static` gives **one shared instance** of `s`
// * All threads **access the same variable**

// ### 🔹 The problem

// * `++s` is **NOT an atomic operation**
// * It expands to:

//   1. Read `s`
//   2. Increment
//   3. Write back

// When **two threads execute this at the same time**, updates are lost.

// This causes:

// * ❌ **Data race**
// * ❌ **Undefined behavior**
// * ❌ Incorrect output (not always `200000`)

// ---

// ## Key Interview Rule (VERY IMPORTANT)

// > **Static ≠ Thread-Safe**

// Static only controls **lifetime**, not **synchronization**.

// ---

// ## How to Make It Thread-Safe ✅ (Option 1: `mutex`)

// ```cpp
// #include <iostream>
// #include <thread>
// #include <mutex>
// using namespace std;

// static int s = 0;
// mutex m;

// void fun() {
//     int count = 100000;
//     while (count--) {
//         lock_guard<mutex> lock(m); // 🔒 Protect shared variable
//         ++s;
//     }
// }

// int main() {
//     thread t1(fun);
//     thread t2(fun);

//     t1.join();
//     t2.join();

//     cout << s << endl;  // ✅ Always 200000
// }
// ```

// ### ✔ Why this works

// * Mutex ensures **only one thread modifies `s` at a time**
// * Prevents race conditions

// ---

// ## Better Modern Solution ✅ (Option 2: `std::atomic`)

// ```cpp
// #include <iostream>
// #include <thread>
// #include <atomic>
// using namespace std;

// static atomic<int> s(0);   // ✅ Thread-safe

// void fun() {
//     int count = 100000;
//     while (count--) {
//         ++s;              // Atomic increment
//     }
// }

// int main() {
//     thread t1(fun);
//     thread t2(fun);

//     t1.join();
//     t2.join();

//     cout << s << endl;     // ✅ Always correct
// }
// ```

// ### ✔ Why this is best

// * Lock-free
// * Faster than mutex
// * Designed for counters

// ---

// ## Interview Cheat Sheet 🧠

// | Statement                                | True / False |
// | ---------------------------------------- | ------------ |
// | Static variable is shared across threads | ✅ True       |
// | Static variable is thread-safe           | ❌ False      |
// | `++s` is atomic                          | ❌ False      |
// | Mutex makes static safe                  | ✅ True       |
// | `std::atomic` makes static safe          | ✅ True       |

// ---

// ## One-Line Interview Answer (Perfect)

// > **“A static variable is shared across threads but is not thread-safe by default; synchronization like mutex or atomic is required.”**

// -