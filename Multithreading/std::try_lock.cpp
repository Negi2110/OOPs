// =============================================================
// std::try_lock() in C++11 Multithreading
// =============================================================
//
// 1. std::try_lock() attempts to lock ALL the lockable objects
//    passed to it, one by one, in the given order.
//
//    Syntax:
//      std::try_lock(m1, m2, m3, ..., mn);
//
//    Each argument must be a lockable object
//    (e.g., std::mutex, std::timed_mutex, etc.)
//
// -------------------------------------------------------------
// RETURN VALUE
// -------------------------------------------------------------
//
// 2. If std::try_lock() SUCCESSFULLY locks ALL mutexes:
//      - It returns -1
//
// 3. If std::try_lock() FAILS to lock any mutex:
//      - It returns the ZERO-BASED INDEX of the mutex
//        that could NOT be locked.
//
//    Example:
//      std::try_lock(m1, m2, m3)
//      return value = 1  -> means m2 could not be locked
//
// -------------------------------------------------------------
// FAILURE BEHAVIOR (VERY IMPORTANT)
// -------------------------------------------------------------
//
// 4. If std::try_lock() fails to lock any mutex:
//      - It automatically UNLOCKS all mutexes
//        that it successfully locked earlier.
//
//    This guarantees:
//      - No partial locking
//      - No deadlock
//      - Exception safety
//
// -------------------------------------------------------------
// EXCEPTION SAFETY
// -------------------------------------------------------------
//
// 5. If an exception occurs during std::try_lock():
//      - unlock() is called on all mutexes
//        that were successfully locked
//      - The exception is then rethrown
//
//    This provides STRONG exception safety.
//
// -------------------------------------------------------------
// INTERVIEW NOTES
// -------------------------------------------------------------
//
// • std::try_lock() is NON-BLOCKING.
// • It does NOT wait for any mutex.
// • It attempts each mutex ONCE.
// • Useful when multiple mutexes must be acquired
//   without risking deadlock.
//
// -------------------------------------------------------------
// INTERVIEW ONE-LINER
// -------------------------------------------------------------
//
// std::try_lock() attempts to lock multiple mutexes without blocking;
// it either locks all of them or none, ensuring deadlock-free behavior.
// =============================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Shared resources
int X = 0;
int Y = 0;

// Two separate mutexes protecting X and Y
std::mutex m1, m2;

// Utility function to simulate work
void doSomeWorkForSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// ------------------------------------------------------------
// incrementXY()
// ------------------------------------------------------------
// This function is executed by TWO different threads:
//
// Thread t1 -> works on X using mutex m1
// Thread t2 -> works on Y using mutex m2
//
// Each thread:
// 1. Locks its respective mutex
// 2. Increments X or Y
// 3. Prints the value
// 4. Unlocks the mutex
// 5. Sleeps for 1 second
//
// NOTE:
// - X and Y are protected independently
// - No deadlock possible here because each thread
//   uses only ONE mutex
// ------------------------------------------------------------
void incrementXY(int& XorY, std::mutex& m, const char* desc) {
    for (int i = 0; i < 5; ++i) {
        m.lock();                 // Acquire lock (blocking)
        ++XorY;                   // Safely modify shared variable
        cout << desc << " = " << XorY << endl;
        m.unlock();               // Release lock
        doSomeWorkForSeconds(1);  // Simulate work
    }
}

// ------------------------------------------------------------
// consumeXY()
// ------------------------------------------------------------
// This function runs in thread t3.
//
// Purpose:
// - Consume X and Y together
// - Add (X + Y) to XplusY
// - Reset X and Y to 0
//
// KEY POINT: std::try_lock(m1, m2)
//
// Execution behavior:
// 1. try_lock attempts to lock BOTH m1 and m2
// 2. If it succeeds:
//      - lockResult == -1
//      - BOTH mutexes are locked
// 3. If it fails:
//      - try_lock releases any mutex it locked
//      - returns index of mutex that failed
//      - thread continues looping (non-blocking)
//
// This avoids DEADLOCK and BLOCKING.
// ------------------------------------------------------------
void consumeXY() {
    int useCount = 5;   // Number of times to consume X and Y
    int XplusY = 0;

    while (1) {

        // Try to lock BOTH mutexes without blocking
        int lockResult = std::try_lock(m1, m2);

        // If BOTH locks are acquired successfully
        if (lockResult == -1) {

            // Check if both values are non-zero
            if (X != 0 && Y != 0) {
                --useCount;

                // Safely read and consume shared data
                XplusY += X + Y;

                // Reset shared variables
                X = 0;
                Y = 0;

                cout << "XplusY = " << XplusY << "\n";
            }

            // IMPORTANT:
            // Since try_lock locked BOTH mutexes,
            // we MUST unlock BOTH
            m1.unlock();
            m2.unlock();

            // Exit loop after consuming required number of times
            if (useCount == 0)
                break;
        }

        // If try_lock fails:
        // - No blocking
        // - No waiting
        // - Loop retries immediately
    }
}

// ------------------------------------------------------------
// main()
// ------------------------------------------------------------
// Thread creation:
//
// t1 -> increments X using mutex m1
// t2 -> increments Y using mutex m2
// t3 -> consumes X and Y together using std::try_lock
//
// Execution highlights:
// - t1 and t2 run independently
// - t3 waits until it can lock BOTH m1 and m2
// - try_lock prevents deadlock
// - Program terminates cleanly after joins
// ------------------------------------------------------------
int main() {

    std::thread t1(incrementXY, std::ref(X), std::ref(m1), "X");
    std::thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y");
    std::thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
// std::try_lock() is NON-BLOCKING.
//
// It does NOT wait for mutexes to become available.
// It attempts to lock each mutex ONCE and returns immediately.
//
// If all mutexes are locked successfully:
//   -> returns -1
//
// If any mutex is already locked:
//   -> unlocks all previously locked mutexes
//   -> returns index of the failed mutex
//
// Any repeated checking happens due to user code (loops),
// not because std::try_lock blocks or waits.
//exaple here we use loop to retry locking
// until we succeed in locking both mutexes.