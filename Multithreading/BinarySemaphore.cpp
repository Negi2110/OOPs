#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std;

/*
 GLOBAL BINARY SEMAPHORES
 -----------------------
 - Both semaphores are initialized with value 0
 - This means they are in a NON-SIGNALED state
 - Any thread calling acquire() will block
*/

// Used by main thread to signal worker thread
std::binary_semaphore smphSignalMainToThread(0);

// Used by worker thread to signal main thread
std::binary_semaphore smphSignalThreadToMain(0);

/*
 Thread procedure executed by the worker thread
*/
void ThreadProc()
{
    /*
     Wait for signal from main thread.
     acquire() blocks until semaphore count > 0.
    */
    smphSignalMainToThread.acquire();

    /*
     This line executes only after main thread
     releases the semaphore.
    */
    cout << "[thread] Got the signal\n";

    /*
     Simulate some work by sleeping for 3 seconds
    */
    using namespace std::literals;
    this_thread::sleep_for(3s);

    /*
     Notify main thread that work is complete
    */
    cout << "[thread] Send the signal\n";
    smphSignalThreadToMain.release();
}

int main()
{
    /*
     Create a worker thread.
     Thread starts execution immediately.
    */
    thread worker(ThreadProc);

    /*
     Simulate main thread work before signaling worker
    */
    cout << "[main] Doing some work...\n";
    this_thread::sleep_for(2s);

    /*
     Signal worker thread to proceed.
     This unblocks acquire() in ThreadProc().
    */
    cout << "[main] Sending signal to thread\n";
    smphSignalMainToThread.release();

    /*
     Wait for worker thread to signal completion
    */
    smphSignalThreadToMain.acquire();
    cout << "[main] Received signal from thread\n";

    /*
     Wait for worker thread to finish execution
    */
    worker.join();

    return 0;
}

// ## 🧠 What This Code Demonstrates (Interview Perspective)

// ### ✔ Binary Semaphore (`std::binary_semaphore`)

// * Used for **one-to-one signaling**
// * Value is either **0 or 1**
// * Similar to a mutex, but **used for signaling**, not mutual exclusion

// ### ✔ Thread Synchronization

// * Main thread controls **when the worker starts**
// * Worker thread signals **when it finishes**

// ### ✔ `acquire()` vs `release()`

// | Function    | Meaning                         |
// | ----------- | ------------------------------- |
// | `acquire()` | Wait / block until signaled     |
// | `release()` | Signal / unblock waiting thread |

// ---

// ## 🧠 Execution Flow (Very Important)

// 1. Worker thread starts → blocks on `acquire()`
// 2. Main thread sleeps → then calls `release()`
// 3. Worker resumes → does work → signals main
// 4. Main thread resumes → joins worker

// ---

// ## ✅ One-Line Interview Explanation

// > *“This program demonstrates inter-thread signaling using binary semaphores, where the main thread controls execution flow and synchronizes completion with a worker thread.”*

// ---

// ## ⚠ Interview Follow-Up (Impress the Interviewer)

// You can say:

// > *“Binary semaphores are ideal for signaling, while mutexes are better suited for protecting shared data.”*

// ---

// ## 🧩 Bonus Interview Q&A

// **Q: Why not use mutex here?**
// 👉 Mutex is for **mutual exclusion**, not signaling.

// **Q: Is this better than condition variables?**
// 👉 Simpler for **one-shot signals**, condition variables are better for complex conditions.


// ## ❌ Error

// > `namespace "std" has no member "binary_semaphore"`

// ---

// ## ✅ Why this happens

// ### 1️⃣ `std::binary_semaphore` is **C++20 only**

// * `std::binary_semaphore` is defined in **C++20**
// * Header:

//   ```cpp
//   #include <semaphore>
//   ```
// * If you compile with:

//   * C++17
//   * C++14
//   * C++11
//     ❌ it **does not exist**

// So the compiler error means **your compiler is not using C++20** (or doesn’t fully support it).

// ---

// ## ✅ How to FIX it (Option 1: Enable C++20)

// ### 🔹 GCC / Clang

// ```bash
// g++ -std=c++20 main.cpp
// ```

// ### 🔹 MSVC (Visual Studio)

// * Project Properties → C/C++ → Language
// * Set **C++ Language Standard** → **ISO C++20 (/std:c++20)**

// Then this works:

// ```cpp
// #include <semaphore>
// std::binary_semaphore sem(0);
// ```

// ---

// ## ❌ If You CAN’T Use C++20 (Very Common)

// Many systems / interviews / companies still use **C++17**.
// In that case → **you must NOT use `binary_semaphore`**.

// ---

// ## ✅ Correct C++11 / C++17 Replacement (Recommended)

// ### Use `std::mutex + std::condition_variable`

// This is the **standard and portable solution**.

// ### ✔ Equivalent Code (C++11+)

// ```cpp
// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <condition_variable>

// using namespace std;

// mutex mtx;
// condition_variable cv;
// bool ready = false;

// void worker() {
//     unique_lock<mutex> lock(mtx);

//     // Wait until main thread signals
//     cv.wait(lock, [] { return ready; });

//     cout << "[thread] Got the signal\n";

//     // Notify main thread
//     ready = false;
//     cv.notify_one();
// }

// int main() {
//     thread t(worker);

//     {
//         lock_guard<mutex> lock(mtx);
//         ready = true;
//         cout << "[main] Sending signal\n";
//     }
//     cv.notify_one();

//     t.join();
//     return 0;
// }
// ```

// ---

// ## 🧠 Interview-Safe Explanation (VERY IMPORTANT)

// > **“`std::binary_semaphore` is a C++20 feature. If the compiler is older, we use `mutex` and `condition_variable` to achieve the same signaling behavior.”**

// This answer scores **full marks**.

// ---

// ## ✅ Comparison Table (Interview Gold)

// | Feature        | `binary_semaphore` | `condition_variable` |
// | -------------- | ------------------ | -------------------- |
// | C++ version    | C++20              | C++11+               |
// | Simplicity     | Very simple        | More code            |
// | Portability    | Lower              | Very high            |
// | Signaling      | Yes                | Yes                  |
// | Mutex required | No                 | Yes                  |

// ---

// ## ✅ Final Verdict

// * ❌ Error is **NOT your fault**
// * ✔ You’re compiling **below C++20**
// * ✔ Either:

//   * Enable **C++20**
//   * OR use **condition_variable** (recommended)

