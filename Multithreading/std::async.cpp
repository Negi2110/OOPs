// =====================================================
// TOPIC: std::async in C++ (C++11 and later)
// =====================================================
//
// PURPOSE (Interview Perspective):
// std::async is used to run a function asynchronously
// and automatically obtain its result via std::future.
//
// It is a HIGH-LEVEL abstraction over:
// - std::thread
// - std::promise
// - std::future
//
// -----------------------------------------------------
// KEY POINTS ABOUT std::async
// -----------------------------------------------------
//
// 1. std::async runs a function asynchronously
//    (either in a new thread or lazily).
//
// 2. It RETURNS a std::future object immediately.
//
// 3. The returned future:
//    - holds the result of the function
//    - blocks when get() is called until result is ready
//
// 4. You do NOT need to explicitly create:
//    - std::thread
//    - std::promise
//    - std::future (created automatically)
//
// -----------------------------------------------------
// LAUNCH POLICIES
// -----------------------------------------------------
//
// std::launch::async
// - Forces execution in a new thread
// - Task starts immediately
//
// std::launch::deferred
// - Task does NOT run immediately
// - Runs ONLY when future.get() or future.wait() is called
// - Runs in the SAME thread (lazy execution)
//
// std::launch::async | std::launch::deferred
// - Let the implementation decide
//
// -----------------------------------------------------
// HOW std::async WORKS INTERNALLY
// -----------------------------------------------------
//
// 1. Creates an internal promise
// 2. Creates an internal future linked to that promise
// 3. Executes the function (immediately or later)
// 4. Stores the return value into the promise
// 5. future.get() retrieves the value
//
// -----------------------------------------------------
// IMPORTANT INTERVIEW NOTES
// -----------------------------------------------------
//
// - future.get() BLOCKS until result is available
// - Function return value is transferred via future
// - Exceptions thrown inside async function
//   are rethrown when future.get() is called
//
// -----------------------------------------------------
// WHEN TO USE std::async
// -----------------------------------------------------
//
// - One-time asynchronous computation
// - When you only care about the result
// - Cleaner alternative to thread + promise + future
//
// -----------------------------------------------------
// WHEN NOT TO USE std::async
// -----------------------------------------------------
//
// - Fine-grained thread control required
// - Long-lived background threads
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <future>
using namespace std;
using namespace std::chrono;
typedef long int ull;

ull find_odd(ull start, ull end) {
    cout << "Finding odd sum from " << start << " to " << end << endl;
    ull oddSum = 0;
    for (ull i = start; i <= end; i++) {
        if (i % 2 != 0) {
            oddSum += i;
        }
    }
    return oddSum;
}

int main() {
    ull start = 0, end = 1900000000;
    cout << "Thread created if policy is std::launch::async" << endl;
    std::future<ull> OddSum = std::async(std::launch::async, find_odd, start, end);
    cout << "Waiting for result..." << endl;
    cout << "oddSum:" << OddSum.get() << endl;
    cout << "Completed" << endl;
    return 0;
}



// ⭐ One-Line Interview Answer
// // std::async runs a function asynchronously and returns
// // a future that provides access to the result.

// 🧠 std::async vs std::thread (Interview Trap)
// // std::thread:
// // - Manual thread management
// // - No return value directly
// //
// // std::async:
// // - Automatic thread + promise + future
// // - Return value via future
// // - Safer and simpler
// std::launch::async:
// - Executes immediately
// - Runs in a separate thread
// - True parallelism
//
// std::launch::deferred:
// - Executes only on get()/wait()
// - Runs in calling thread
// - No parallelism
//
// Default std::async:
// - Implementation decides
// - May behave as async OR deferred
// “std::launch::async runs immediately in a new thread, while std::launch::deferred runs lazily in the calling thread when get() is invoked.”

// std::launch::async:
// - Function runs immediately
// - Runs in a NEW thread
// - True asynchronous execution
//
// std::launch::deferred:
// - Function does NOT run immediately
// - Runs ONLY when future.get() or wait() is called
// - Runs in the SAME thread that calls get()
// - No new thread is created
// ⭐ One-Line Interview Answer (Perfect)
// “std::launch::async runs the task in a new thread immediately, while std::launch::deferred runs the task lazily in the calling thread when get() is invoked.”