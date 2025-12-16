// =============================================================
// TOPIC: Thread or Process Synchronization
// =============================================================
//
// NOTE:
// In this explanation, we focus ONLY on THREAD synchronization.
// The same concepts apply to process synchronization,
// but the mechanisms (mutex, semaphore, etc.) may differ.
//
// -------------------------------------------------------------
// WHAT IS SYNCHRONIZATION?
// -------------------------------------------------------------
//
// Synchronization is the technique used to COORDINATE
// the execution of multiple threads or processes
// so that shared resources are accessed safely and correctly.
//
// -------------------------------------------------------------
// WHY SYNCHRONIZATION IS NEEDED
// -------------------------------------------------------------
//if you are just reading data,no need of synchronization=>no critical section
//if you are modifying data=>need synchronization=>critical section
// When multiple threads run concurrently:
// - They may access shared data
// - They may modify the same resource at the same time
//
// This can cause:
// - Race conditions
// - Data inconsistency
// - Undefined behavior
//
// Synchronization prevents these problems.
//
// -------------------------------------------------------------
// CRITICAL SECTION
// -------------------------------------------------------------
//
// A critical section is:
// - A single statement OR
// - A block (collection) of statements
//
// that MUST be executed by ONLY ONE thread (or process)
// at a time.
//
// Example:
//   Updating a shared variable
//   Writing to a file
//   Accessing shared memory
//
// -------------------------------------------------------------
// RELATION BETWEEN SYNCHRONIZATION & CRITICAL SECTION
// -------------------------------------------------------------
//
// Synchronization is USED TO:
// - Protect critical sections
// - Ensure exclusive access
//
// Critical section is the "WHAT"
// Synchronization mechanism (mutex, lock, etc.) is the "HOW"
//
// -------------------------------------------------------------
// THREAD-LEVEL SYNCHRONIZATION
// -------------------------------------------------------------
//
// In thread synchronization:
// - Threads share the same memory space
// - Mutexes, condition variables, atomics are commonly used
//
// Example mechanisms:
// - std::mutex
// - std::lock_guard
// - std::unique_lock
// - std::condition_variable
//
// -------------------------------------------------------------
// INTERVIEW ONE-LINER
// -------------------------------------------------------------
//
// "Thread synchronization ensures that critical sections
// are accessed by only one thread at a time, preventing
// race conditions and ensuring data consistency."
// =============================================================
// ```

// ### ⭐ Quick interview tip

// If the interviewer asks:

// > **“What is the difference between synchronization and critical section?”**

// Answer:

// > **“A critical section is the code that needs protection, while synchronization is the mechanism used to protect it.”**

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
//std::mutex mtx; //mutex object
long long bankBalance = 0;
void addMoney(long long val)
{
    //mtx.lock();               //start of critical section
    bankBalance += val;
    //mtx.unlock();             //end of critical section
}
int main()
{
    std::thread t1(addMoney, 1000);
    std::thread t2(addMoney, 2000);
    t1.join();
    t2.join();
    cout << "Final Bank Balance: " << bankBalance << endl;
    return 0;
}
//1.load bankBalance in register
//2.add val to register
//3.store register to bankBalance