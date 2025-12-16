// =============================================================
// TOPIC: Condition Variable in C++ Threading
// =============================================================
//
// A condition_variable is used for THREAD COORDINATION.
// It allows threads to:
// 1) WAIT for a condition to become true
// 2) NOTIFY other threads when the condition is satisfied
//
// -------------------------------------------------------------
// PURPOSES OF CONDITION VARIABLE
// -------------------------------------------------------------
//
// A. Notify other threads
// B. Make threads wait efficiently (without busy waiting)
//
// -------------------------------------------------------------
// WHAT PROBLEM IT SOLVES
// -------------------------------------------------------------
//
// Without condition variables:
// - Threads keep checking a condition in a loop (busy waiting)
// - This wastes CPU cycles
//
// With condition variables:
// - Thread sleeps until notified
// - CPU is not wasted
//
// -------------------------------------------------------------
// WHY MUTEX IS REQUIRED
// -------------------------------------------------------------
//
// Condition variables DO NOT protect shared data.
// They must ALWAYS be used with a mutex.
//
// The mutex protects the shared condition/state.
// The condition_variable only handles waiting & notification.
//
// -------------------------------------------------------------
// HOW A THREAD WAITS (IMPORTANT FLOW)
// -------------------------------------------------------------
//
// If a thread wants to wait on a condition, it must:
//
// 1) Acquire the mutex using std::unique_lock
// 2) Call wait(), wait_for(), or wait_until()
// 3) wait() will:
//    - Atomically RELEASE the mutex
//    - SUSPEND the thread
// 4) When notified:
//    - Thread wakes up
//    - Mutex is AUTOMATICALLY re-acquired
// 5) Thread checks the condition again
//
// -------------------------------------------------------------
// WHY CONDITION MUST BE CHECKED AGAIN
// -------------------------------------------------------------
//
// Because of SPURIOUS WAKEUPS:
// - Thread may wake up even if no notification was sent
// - Or condition may still be false
//
// Hence ALWAYS check condition in a loop or predicate.
//
// -------------------------------------------------------------
// CORRECT WAIT PATTERN
// -------------------------------------------------------------
//
// cv.wait(lock, [] { return condition == true; });
//
// This ensures:
// - Thread sleeps until condition becomes true
// - Automatically handles spurious wakeups
//
// -------------------------------------------------------------
// NOTIFICATION METHODS
// -------------------------------------------------------------
//
// 1) notify_one()
//    - Wakes ONE waiting thread
//
// 2) notify_all()
//    - Wakes ALL waiting threads
//
// -------------------------------------------------------------
// WHAT HAPPENS ON NOTIFY
// -------------------------------------------------------------
//
// - A waiting thread is awakened
// - It re-acquires the mutex
// - It checks the condition
// - Continues execution if condition is satisfied
//
// -------------------------------------------------------------
// BEST USE CASE
// -------------------------------------------------------------
//
// Producer–Consumer Problem:
//
// Producer:
// - Produces data
// - Sets condition = true
// - Calls notify_one()
//
// Consumer:
// - Waits for condition
// - Consumes data
//
// -------------------------------------------------------------
// IMPORTANT NOTES
// -------------------------------------------------------------
//
// - Condition variables synchronize THREADS, not data
// - Always use std::unique_lock (not lock_guard)
// - wait() releases and re-acquires mutex atomically
//
// -------------------------------------------------------------
// INTERVIEW ONE-LINER
// -------------------------------------------------------------
//
// "A condition variable allows a thread to sleep efficiently
// until another thread signals that a condition has changed."
// =============================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// =============================================================
// Shared resources
// =============================================================

// Condition variable is used to make threads WAIT and NOTIFY
std::condition_variable cv;

// Mutex protects access to shared data (balance)
std::mutex m;

// Shared data between threads
long balance = 0;

// =============================================================
// Producer function: Adds money
// =============================================================
void addMoney(int money)
{
    // lock_guard is used because:
    // - We just need a simple lock
    // - Lock is held for the entire scope
    std::lock_guard<mutex> lg(m);

    // Critical Section: modifying shared data
    balance += money;

    cout << "Amount Added. Current balance: " << balance << endl;

    // Notify ONE waiting thread that balance has changed
    // This wakes up the thread waiting on cv.wait()
    cv.notify_one();
}

// =============================================================
// Consumer function: Withdraws money
// =============================================================
void withdrowMoney(int money)
{
    // unique_lock is REQUIRED with condition_variable
    // because it allows:
    // - unlocking while waiting
    // - re-locking when notified
    std::unique_lock<mutex> ul(m);

    cout << "Going to withdraw money: " << money << endl;

    // Thread waits until balance becomes non-zero
    //
    // IMPORTANT INTERVIEW POINT:
    // - wait() releases the mutex atomically
    // - thread is put to sleep (no CPU waste)
    // - when notified, mutex is re-acquired automatically
    //
    // Predicate protects against spurious wakeups
    cv.wait(ul, [] {
        return balance != 0;
    });

    // After waking up, mutex is locked again
    // Safe to access shared data
    if (balance >= money)
    {
        balance -= money;
        cout << "Amount deducted: " << money << endl;
    }
    else
    {
        cout << "Amount can't be deducted, current balance is less than "
             << money << endl;
    }

    cout << "Current balance: " << balance << endl;
}

// =============================================================
// Main function
// =============================================================
int main()
{
    // Thread t1 tries to withdraw money FIRST
    // Since balance = 0, it will go into waiting state
    std::thread t1(withdrowMoney, 500);
    //std::this_thread::sleep_for(std::chrono::seconds(2));-main thread sleep 

    // Thread t2 adds money
    // It updates balance and notifies waiting thread
    std::thread t2(addMoney, 500);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}


// ### What problem does this program solve?

// > It demonstrates **thread synchronization using condition variables**, avoiding busy waiting.

// ---

// ### Why is `condition_variable` needed?

// > To make a thread **sleep efficiently** until a condition (balance update) is satisfied.

// ---

// ### Why `unique_lock` instead of `lock_guard` in `withdrowMoney`?

// > Because `condition_variable::wait()` needs the ability to **unlock and re-lock** the mutex.

// ---

// ### What happens during `cv.wait()`?

// 1. Mutex is released
// 2. Thread goes to sleep
// 3. Another thread modifies shared data
// 4. `notify_one()` wakes the waiting thread
// 5. Mutex is re-acquired automatically
// 6. Condition is re-checked

// ---

// ### Why predicate is important?

// > To handle **spurious wakeups** safely.

// ---

// ## ⭐ One-Line Interview Summary

// > **“Condition variables allow threads to wait efficiently until a condition becomes true, releasing the mutex while waiting and re-acquiring it upon notification.”**

