// TOPIC: std::mutex::try_lock() in C++ Multithreading

// 0. try_lock() attempts to lock the mutex WITHOUT blocking.
//    It returns immediately.
//    - Returns true  -> if the mutex was successfully locked.
//    - Returns false -> if the mutex is already locked by another thread.

// 1. If try_lock() is NOT able to lock the mutex,
//    the calling thread does NOT get blocked.
//    This is why try_lock() is called a non-blocking lock.

// 2. If try_lock() is called again by the SAME thread
//    while it already owns the mutex,
//    the behavior is UNDEFINED for std::mutex.
//    (If you need the same thread to lock the mutex multiple times,
//     you must use std::recursive_mutex instead.)

// 3. Using try_lock() incorrectly can lead to logical errors
//    if the return value is not checked before accessing
//    the critical section.

// INTERVIEW NOTE:
// try_lock() is useful when a thread wants to attempt
// to acquire a lock and do something else if the lock
// is not immediately available, instead of waiting.
// In this loop, try_lock() checks the mutex ONLY ONCE per iteration.
//
// If the mutex is already locked:
// - try_lock() returns false
// - The increment is SKIPPED
// - The loop moves to the next iteration
//
// The thread does NOT wait.
// The thread does NOT retry automatically.
//
// As a result:
// - Many increments are lost
// - Final counter value is NON-deterministic
// - Final value is less than expected
//
// This is NOT a race condition.
// This is intentional behavior caused by try_lock().

#include <iostream>
#include <thread>
#include <mutex>
 using namespace std;
 int counter=0;
 std::mutex mtx;
 void incrementCounter() {
    for(int i=0; i<100000; ++i) {
     if (mtx.try_lock()) {
         ++counter;
         mtx.unlock();
     }
    // //if u want to see count to 200000 then use lock instead of try_lock
    // mtx.lock();
    // ++counter;
    // mtx.unlock();
 }
}
int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);
    t1.join();
    t2.join();
    std::cout << "Final Counter Value: " << counter << std::endl;
    return 0;
}

// There are many try_lock() functions available in C++ threading:
//
// 1. std::mutex::try_lock()
//    - Non-blocking attempt to lock a mutex.
//
// 2. std::timed_mutex::try_lock()
//    - Non-blocking attempt to lock a timed mutex.
//
// 3. std::recursive_mutex::try_lock()
//    - Allows the SAME thread to lock the mutex multiple times.
//
// 4. std::recursive_timed_mutex::try_lock()
//    - Recursive mutex with timing support.
//
// 5. std::shared_mutex::try_lock()
//    - Tries to acquire an exclusive (write) lock.
//
// 6. std::shared_timed_mutex::try_lock()
//    - Timed version of shared_mutex (C++14, deprecated in C++20).
//
// 7. std::shared_mutex::try_lock_shared()
//    - Tries to acquire a shared (read) lock.
//
// 8. std::shared_timed_mutex::try_lock_shared()
//    - Timed version of shared shared lock.
//
// 9. std::unique_lock<Mutex>::try_lock()
//    - RAII-based non-blocking lock attempt.
//
// 10. std::shared_lock<SharedMutex>::try_lock()
//     - RAII wrapper for shared (read) locks.


// ### ⭐ **Interview Tip (Very Important)**

// ```cpp
// NOTE:
// try_lock() should ALWAYS be followed by checking its return value.
// Failing to do so can cause race conditions or logic bugs.

// Two threads run the same function concurrently.
// Each thread executes its own loop (100000 iterations).
//
// In each iteration:
// - try_lock() is called once
// - If mutex is free → counter is incremented
// - If mutex is busy → iteration is skipped
//
// Threads do NOT wait.
// Threads do NOT retry automatically.
//
// Total attempts = 200000
// Successful increments < 200000
// IMPORTANT CLARIFICATION:
//
// The mutex (mtx) and the shared resource (counter)
// are COMMON and SHARED between both threads.
//
// However:
// - Only ONE thread can hold the mutex at a time.
// - If a thread calls try_lock() while the mutex is held,
//   the call FAILS immediately.
// - That iteration is SKIPPED.
// - The shared resource is NOT modified in that iteration.
//
// Sharing the resource does NOT mean every iteration
// will get a chance to execute the critical section.
//
// try_lock() guarantees safety (no race condition),
// but NOT completeness (no guarantee that every attempt succeeds).


// If counter is declared inside the function:
//
// - Each thread gets its OWN copy of counter.
// - The variable is stored on the thread's stack.
// - There is NO sharing between threads.
// - No race condition occurs.
// - No mutex is required.
//
// Mutexes are only needed for SHARED resources.
// If counter is declared inside the function:
//
// - Each thread gets its OWN copy of counter.
// - counter is NOT shared.
// - Each thread increments its own counter 100000 times.
// - Each thread ends with counter = 100000.
// - No mutex is required.


// The final counter value will vary on every execution.
// Reason:
// - try_lock() does not block
// - Failed lock attempts are skipped
// - Thread scheduling is nondeterministic
//
// Therefore, the program is thread-safe
// but produces a non-deterministic result.
