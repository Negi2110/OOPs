// =============================================================
// TOPIC: std::unique_lock in C++ (std::unique_lock<std::mutex>)
// =============================================================
//
// std::unique_lock is a MUTEX OWNERSHIP WRAPPER.
// It manages locking and unlocking of a mutex using RAII,
// but provides MORE flexibility than std::lock_guard.
//
// -------------------------------------------------------------
// KEY CHARACTERISTICS
// -------------------------------------------------------------
//
// 1. Owns a mutex (just like lock_guard).
// 2. Automatically unlocks the mutex when it goes out of scope.
// 3. Allows DEFERRED locking (lock later).
// 4. Allows TRY locking (non-blocking).
// 5. Supports TIMED locking (with timed_mutex).
// 6. Ownership can be TRANSFERRED (moveable, not copyable).
// 7. Can be manually locked/unlocked.
// 8. Required when using condition variables.
//
// -------------------------------------------------------------
// WHY unique_lock EXISTS
// -------------------------------------------------------------
//
// std::lock_guard is very strict:
// - Locks immediately
// - Unlocks only at scope exit
// - No flexibility
//
// std::unique_lock is more powerful and flexible:
// - Lock when needed
// - Unlock early if required
// - Re-lock again
//
// -------------------------------------------------------------
// LOCKING STRATEGIES (CONSTRUCTORS)
// -------------------------------------------------------------
//
// 1. std::defer_lock
//    - Does NOT lock the mutex at construction
//    - Lock must be called explicitly later
//
//    Example:
//    std::unique_lock<std::mutex> lock(m, std::defer_lock);
//    lock.lock();
//
// -------------------------------------------------------------
//
// 2. std::try_to_lock
//    - Tries to lock the mutex WITHOUT blocking
//    - If mutex is busy, lock is NOT acquired
//
//    Example:
//    std::unique_lock<std::mutex> lock(m, std::try_to_lock);
//    if (lock.owns_lock()) {
//        // critical section
//    }
//
// -------------------------------------------------------------
//
// 3. std::adopt_lock
//    - Assumes the mutex is ALREADY locked by the calling thread
//    - unique_lock takes ownership without locking again
//
//    Example:
//    m.lock();
//    std::unique_lock<std::mutex> lock(m, std::adopt_lock);
//
// -------------------------------------------------------------
// OWNERSHIP BEHAVIOR
// -------------------------------------------------------------
//
// - unique_lock CANNOT be copied
// - unique_lock CAN be moved
//
// This allows transfer of mutex ownership between scopes/functions
//
// -------------------------------------------------------------
// MANUAL CONTROL
// -------------------------------------------------------------
//
// unique_lock allows:
//
//   lock.lock();     // lock mutex
//   lock.unlock();   // unlock mutex
//   lock.try_lock(); // try lock without blocking
//
// This is NOT possible with lock_guard.
//
// -------------------------------------------------------------
// CONDITION VARIABLE SUPPORT
// -------------------------------------------------------------
//
// std::condition_variable REQUIRES std::unique_lock
// because it needs to temporarily unlock and re-lock the mutex.
//
// lock_guard CANNOT be used with condition_variable.
//
// -------------------------------------------------------------
// PERFORMANCE NOTE
// -------------------------------------------------------------
//
// std::unique_lock has SLIGHT overhead compared to lock_guard
// due to its flexibility.
//
// -------------------------------------------------------------
// WHEN TO USE WHAT (INTERVIEW ANSWER)
// -------------------------------------------------------------
//
// Use std::lock_guard:
// - Simple critical section
// - Lock for entire scope
// - Maximum performance
//
// Use std::unique_lock:
// - Need deferred locking
// - Need try_lock or timed locking
// - Need manual unlock
// - Using condition variables
//
// -------------------------------------------------------------
// ONE-LINE INTERVIEW SUMMARY
// -------------------------------------------------------------
//
// "std::unique_lock is a flexible mutex ownership wrapper that
// supports deferred, try, and timed locking, unlike lock_guard."
// =============================================================
//you cant not have two ownerships of the same mutex
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
std::mutex m1;
int buffer = 0;

//example-1

// void task(const char* threadNumber, int loopFor) {
//     std::unique_lock<std::mutex> lock(m1); // locks mutex
//     for (int i = 0; i < loopFor; ++i) {
//         buffer++;
//         cout << "Thread " << threadNumber << ": " << buffer << endl;
//     } // mutex is automatically unlocked when lock goes out of scope
   
// }
//example-2
void task(const char* threadNumber, int loopFor) {
    std::unique_lock<std::mutex> lock(m1, std::defer_lock); // locks mutex
    lock.lock(); // manually lock the mutex
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << "Thread " << threadNumber << ": " << buffer << endl;
    } // mutex is automatically unlocked when lock goes out of scope
   //lock.unlock will not be needed as it will be unlocked automatically unlocked in destructor of unique_lock
}
int main() {
    std::thread t1(task, "T1", 10);
    std::thread t2(task, "T2", 10);
    t1.join();
    t2.join();
    return 0;
}







// A mutex can have ONLY ONE owner at a time.
// Multiple threads cannot own the same mutex simultaneously.
//
// - lock_guard and unique_lock enforce exclusive ownership
// - unique_lock allows ownership transfer (move), not sharing
// - recursive_mutex allows the SAME thread to lock multiple times
