// =============================================================
// TOPIC: lock_guard in C++ (std::lock_guard<std::mutex>)
// =============================================================
//
// std::lock_guard is a LIGHTWEIGHT RAII wrapper
// used to manage a mutex within a SCOPE.
//
// RAII = Resource Acquisition Is Initialization
//
// =============================================================
// KEY FEATURES OF std::lock_guard
// =============================================================
//
// 1. VERY LIGHTWEIGHT
//    - Minimal overhead
//    - No extra functionality beyond lock/unlock
//
// 2. AUTOMATIC LOCKING
//    - Mutex is LOCKED immediately when lock_guard object is created
//
//    Example:
//        std::lock_guard<std::mutex> lock(m);
//
// 3. AUTOMATIC UNLOCKING
//    - Mutex is automatically UNLOCKED when lock_guard
//      goes OUT OF SCOPE (destructor is called)
//
// 4. NO MANUAL UNLOCK
//    - You CANNOT explicitly unlock a lock_guard
//    - Unlocking is strictly scope-based
//
// 5. NON-COPYABLE
//    - lock_guard cannot be copied or assigned
//    - Ensures single ownership of the mutex
//
// =============================================================
// WHY lock_guard IS IMPORTANT
// =============================================================
//
// • Prevents forgetting to unlock a mutex
// • Exception-safe
// • Avoids deadlocks caused by early returns
// • Encourages correct locking discipline
//
// =============================================================
// SIMPLE EXAMPLE
// =============================================================
//
// std::mutex m;
//
// void criticalSection() {
//     std::lock_guard<std::mutex> lock(m);  // mutex locked here
//     // critical section code
// }                                           // mutex unlocked here
//
// =============================================================
// INTERVIEW CLARIFICATIONS
// =============================================================
//
// • lock_guard locks ONLY in constructor
// • unlock happens ONLY in destructor
// • No try_lock
// • No deferred locking
// • Best choice for simple, scoped locking
//
// =============================================================
// lock_guard vs mutex.lock()
// =============================================================
//
// mutex.lock() / mutex.unlock():
// - Manual
// - Error-prone
//
// lock_guard:
// - Automatic
// - Exception-safe
//
// =============================================================
// INTERVIEW ONE-LINER
// =============================================================
//
// "std::lock_guard is a lightweight RAII wrapper that locks
// a mutex on creation and automatically unlocks it when the
// object goes out of scope."
// lock->object
// m1->mutex object
// =============================================================

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Mutex to protect shared resource
std::mutex m1;

// Shared resource
int buffer = 0;

// ------------------------------------------------------------
// task()
// ------------------------------------------------------------
// This function is executed by multiple threads.
//
// PURPOSE:
// - Safely increment and print the shared variable `buffer`
// - Use std::lock_guard to manage the mutex automatically
//
// HOW lock_guard WORKS HERE:
// - As soon as lock_guard object is created, it LOCKS the mutex
// - The mutex remains locked for the entire scope of the function
// - When the function ends (scope ends), lock_guard is destroyed
// - The DESTRUCTOR of lock_guard automatically UNLOCKS the mutex
//
// IMPORTANT:
// - No need to call m1.lock() or m1.unlock() manually
// - Prevents forgetting to unlock the mutex
// - Exception-safe and early-return safe
// ------------------------------------------------------------
void task(const char *threadName, int loopFor)
{
    // const means “read-only” — the value must NOT be modified.”
    //  const char* means:
    // - Pointer to a character array
    // - The characters being pointed to are READ-ONLY
    //
    // Ensures const-correctness

    // lock_guard is created here
    // Constructor is called → mutex m1 is LOCKED immediately
    std::lock_guard<std::mutex> lock(m1);

    // Critical Section starts
    for (int i = 0; i < loopFor; ++i)
    {
        ++buffer; // Safe access to shared resource
        cout << threadName << ": " << buffer << endl;
    }
    // Critical Section ends

    // When execution reaches here and the function scope ends:
    // - lock_guard object goes OUT OF SCOPE
    // - Destructor of lock_guard is automatically called
    // - Destructor calls m1.unlock()
    //
    // This guarantees the mutex is ALWAYS unlocked,
    // even if an exception occurs or function returns early.
}

// ------------------------------------------------------------
// main()
// ------------------------------------------------------------
// Two threads execute the SAME function `task()`.
//
// Because of lock_guard:
// - Only ONE thread can execute the critical section at a time
// - The other thread waits until the mutex is unlocked
// - Output is consistent and race-condition free
// ------------------------------------------------------------
// The mutex remains locked until the lock_guard object goes out of scope — which is the END OF THE FUNCTION task(), not the end of the loop.
int main()
{

    thread t1(task, "T0", 10);
    thread t2(task, "T1", 10);

    t1.join();
    t2.join();

    return 0;
}
// A pointer itself does NOT control mutability.
// The 'const' keyword decides whether the data
// being pointed to can be modified.
//
// const char* p  -> data is read-only
// char* p        -> data is modifiable
