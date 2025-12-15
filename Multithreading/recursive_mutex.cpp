// =============================================================
// TOPIC: Recursive Mutex in C++ (std::recursive_mutex)
// =============================================================
//
// std::recursive_mutex is similar to std::mutex,
// BUT it allows the SAME THREAD to lock the SAME mutex
// MULTIPLE TIMES without causing a deadlock.
//
// =============================================================
// HOW recursive_mutex WORKS
// =============================================================
//
// 1. If Thread T1 locks a recursive_mutex for the first time:
//      - Mutex becomes owned by T1
//      - Internal lock count = 1
//
// 2. If the SAME Thread T1 locks it again:
//      - Lock count increments (2, 3, ...)
//      - No deadlock occurs
//
// 3. Each lock() MUST be matched with an unlock():
//      - If locked 3 times → must unlock 3 times
//
// 4. Mutex is released ONLY when lock count reaches ZERO.
//
// =============================================================
// IMPORTANT BEHAVIOR DETAILS
// =============================================================
//
// • If another thread (T2) tries to lock the mutex while
//   T1 still holds it (lock count > 0):
//     -> T2 will BLOCK (or fail if try_lock is used)
//
// • recursive_mutex internally tracks:
//     - Owning thread ID
//     - Lock count
//
// =============================================================
// try_lock() BEHAVIOR
// =============================================================
//
// • try_lock() by SAME thread:
//     -> Succeeds and increments lock count
//
// • try_lock() by DIFFERENT thread:
//     -> Returns false (mutex is owned)
//
// =============================================================
// LOCK LIMIT
// =============================================================
//
// • The maximum recursion depth (lock count) is NOT specified
// • Exceeding it results in:
//     -> Undefined behavior
//     -> Possible std::system_error
//     or if we are using try_lock()
//     -> Returns false
// =============================================================
// WHEN TO USE recursive_mutex
// =============================================================
//
// ✔ When a function locks a mutex and calls another function
//   that tries to lock the SAME mutex again (re-entrancy)
//
// ✔ Common in recursive functions or layered APIs
//
// =============================================================
// WHEN NOT TO USE recursive_mutex
// =============================================================
//
// ✘ When design can be restructured
// ✘ For performance-critical paths
//
// WHY?
// - recursive_mutex has MORE overhead than std::mutex
// - Requires ownership tracking and lock count management
//
// =============================================================
// INTERVIEW BOTTOM LINE
// =============================================================
//
// • recursive_mutex allows SAME thread to lock repeatedly
// • Must unlock SAME number of times
// • Avoid if possible due to performance overhead
//
// -------------------------------------------------------------
// INTERVIEW ONE-LINER
// -------------------------------------------------------------
//
// "std::recursive_mutex allows the same thread to acquire
// the same mutex multiple times, requiring equal unlocks,
// but should be avoided unless re-entrant locking is required."
// =============================================================

// std::mutex:
// - Same thread locking twice → DEADLOCK
//
// std::recursive_mutex:
// - Same thread locking multiple times → OK
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

// // Example 1: With Recursion
// std::recursive_mutex m1;
// int buffer = 0;
// void recursion(char c, int loopFor)
// {
//     if (loopFor < 0)
//     {
//         return;
//     }
//     m1.lock();
//     cout << c << " " << buffer++ << endl;
//     recursion(c, --loopFor);
//     m1.unlock();
//     //cout << c << " unlocked" << endl;
// }
// int main() {
//     std::thread t1(recursion, '1', 10);
//     std::thread t2(recursion, '2', 10);
//     t1.join();
//     t2.join();
//     return 0;
// }

//Example 2: With Loop

std::recursive_mutex m1;

int main() {
	
	for(int i=0; i<5; i++) {
		m1.lock();
		std::cout << "locked " << i << endl;
	}

	for(int i=0; i<5; i++) {
		m1.unlock();
		std::cout << "ulocked " << i << endl;
	}
	
	return 0;
}