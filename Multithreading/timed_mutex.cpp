// =============================================================
// TOPIC: Timed Mutex in C++ Threading (std::timed_mutex)
// =============================================================
//
// NOTE:
// We already understand the following concepts:
// - Mutex
// - Race Condition
// - Critical Section
//
// std::timed_mutex extends std::mutex by allowing
// TIME-BOUND locking attempts.
// =============================================================


// -------------------------------------------------------------
// std::timed_mutex
// -------------------------------------------------------------
//
// A std::timed_mutex allows a thread to attempt to acquire
// a lock for a LIMITED amount of time.
//
// If the mutex is acquired within the time limit:
//   -> lock succeeds
//
// If the time expires before the mutex becomes available:
//   -> lock fails
//
// This avoids indefinite blocking.
// -------------------------------------------------------------


// -------------------------------------------------------------
// Member Functions of std::timed_mutex
// -------------------------------------------------------------
//
// 1. lock()
//    - Blocks the calling thread until the mutex is acquired
//    - Same behavior as std::mutex::lock()
//
// 2. try_lock()
//    - Non-blocking
//    - Tries to acquire the mutex once
//    - Returns true if successful, false otherwise
//
// 3. try_lock_for(duration)
//    - Blocks the thread for AT MOST the given duration
//    - Returns true if lock is acquired within that time
//    - Returns false if timeout expires
//
// 4. try_lock_until(time_point)
//    - Blocks the thread until a specific time point
//    - Returns true if lock is acquired before that time
//    - Returns false if time point is reached
//
// 5. unlock()
//    - Releases the mutex
//
// NOTE:
// try_lock_for() and try_lock_until() are what make
// std::timed_mutex different from std::mutex.
// -------------------------------------------------------------


// -------------------------------------------------------------
// Example: try_lock_for()
// -------------------------------------------------------------
//
// try_lock_for() waits until either:
//   - The mutex is acquired
//   - OR the specified timeout duration has elapsed
//
// Whichever happens FIRST.
//
// On success:
//   -> returns true
//
// On timeout:
//   -> returns false
// -------------------------------------------------------------

/*
std::timed_mutex mtx;

if (mtx.try_lock_for(std::chrono::seconds(2))) {
    // Critical section
    mtx.unlock();
} else {
    // Failed to acquire lock within 2 seconds
}
*/


// -------------------------------------------------------------
// INTERVIEW KEY POINTS
// -------------------------------------------------------------
//
// • std::timed_mutex prevents infinite blocking
// • Useful when threads must remain responsive
// • try_lock_for() and try_lock_until() are blocking
//   BUT time-limited
// • Safer than lock() in time-sensitive systems
//
// -------------------------------------------------------------
// INTERVIEW ONE-LINER
// -------------------------------------------------------------
//
// std::timed_mutex allows threads to attempt locking
// with a timeout, avoiding indefinite blocking.
// =============================================================

// std::mutex        -> lock forever
// std::timed_mutex  -> lock with timeout
//try_lock_for() -> try to lock for a limited time
// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <chrono>
// using namespace std;
//  int myAmount = 0;
//  std::timed_mutex m;
//  void increment(int i) {
//     if(m.try_lock_for(std::chrono::seconds(1))) { // try to lock for 1 second//other thread will wait here for 1 second,if it can't get the lock in 1 second, it will timeout
//         ++myAmount;
//         std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate work//if we uncomment this line, the other thread will timeout
//         cout << "Thread " << i << " incremented myAmount to " << myAmount << endl;
//         m.unlock();
//     } else {
//         cout << "Thread " << i << " could not acquire lock within timeout." << endl;
//     }   
//  }
// int main() {
//     std::thread t1(increment, 1);
//     std::thread t2(increment, 2);
//     t1.join();
//     t2.join();
//     cout << "Final myAmount: " << myAmount << endl;
//     return 0;
// }



//try_lock_until() -> try to lock until a specific time point
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Shared variable accessed by multiple threads
int myAmount = 0;

// timed_mutex allows locking with TIME LIMIT
std::timed_mutex m;

// ------------------------------------------------------------
// increment()
// ------------------------------------------------------------
// This function is executed by multiple threads.
//
// Goal:
// - Try to acquire the mutex for at most 1 second
// - If lock is acquired:
//     * Increment shared variable
//     * Hold the lock for 2 seconds (simulate work)
// - If lock is NOT acquired within time:
//     * Print "Couldn't Enter"
//
// IMPORTANT:
// try_lock_until() is a BLOCKING call,
// but only until the specified TIME POINT.
// ------------------------------------------------------------
void increment(int i) {

    // Get current time point
    auto now = std::chrono::steady_clock::now();

    // Try to acquire the mutex UNTIL (now + 2 seconds)
    if (m.try_lock_until(now + std::chrono::seconds(2))) {

        // Mutex successfully acquired within timeout
        ++myAmount;   // Safe modification of shared resource

        // Simulate long critical section (2 seconds)
        std::this_thread::sleep_for(std::chrono::seconds(1));

        cout << "Thread " << i << " Entered" << endl;

        // Release the mutex
        m.unlock();
    }
    else {
        // Mutex was NOT acquired within 1 second
        // Thread does NOT block forever
        cout << "Thread " << i << " Couldn't Enter" << endl;
    }
}

// ------------------------------------------------------------
// main()
// ------------------------------------------------------------
// Two threads try to enter the critical section.
//
// Behavior:
// - Only ONE thread can acquire the mutex
// - The first thread holds the lock for 2 seconds
// - The second thread waits only 1 second
// - Therefore, the second thread TIMES OUT
// ------------------------------------------------------------
int main() {

    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    // myAmount will be either 1 or 2 depending
    // on which thread acquired the mutex first
    cout << myAmount << endl;

    return 0;
}


