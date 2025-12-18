// ### 📚 Explanation
// TOPIC: std::lock() in C++11
//
// std::lock() is used to lock MULTIPLE mutexes at the same time
// in a DEADLOCK-FREE manner.
//
// IMPORTANT:
// Syntax:
//     std::lock(m1, m2, m3, ..., mn);
//
// HOW IT WORKS:
// 1. std::lock() attempts to acquire all the mutexes passed to it.
// 2. The order of locking is NOT guaranteed (implementation-defined).
// 3. If it fails to lock any mutex:
//      - It releases all mutexes it has already locked
//      - Then retries until all mutexes are acquired
// 4. This strategy prevents deadlock automatically.
//
// BLOCKING BEHAVIOR:
// - std::lock() IS a blocking call
// - The calling thread will wait until ALL mutexes are successfully locked
//
// DEADLOCK PREVENTION:
// - Prevents circular wait by ensuring atomic acquisition of all locks
// - Safer than manually calling m1.lock(); m2.lock();
//
// COMMON USAGE PATTERN:
//
/*
    std::lock(m1, m2);
    std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
*/
//
// NOTE:
// - adopt_lock tells lock_guard that the mutex is already locked
// - lock_guard will now manage unlocking automatically (RAII)
//
// INTERVIEW ONE-LINER:
// “std::lock() atomically locks multiple mutexes and guarantees deadlock avoidance.”
// ```

// ### 🔥 Interview Pitfall (Important)
//lockorder 1 2 3 4(failed to lock) -> unlock 1 2 3 -> retry 4 1 2 3(failed to lock) -> unlock 3 4 -> retry ...
// ```cpp
// // ❌ WRONG (may deadlock):
// m1.lock();
// m2.lock();

// // ✅ CORRECT:
// std::lock(m1, m2);
// ```
// =====================================================
// TOPIC: std::lock() — Deadlock vs No Deadlock Examples
// =====================================================

// RULE TO REMEMBER (Interview Gold):
// std::lock() prevents deadlock ONLY for the mutexes
// passed in the SAME call.

// -----------------------------------------------------
// [Example 0] --> NO DEADLOCK
// -----------------------------------------------------

// // Thread 1:
// std::lock(m1, m2);

// // Thread 2:
// std::lock(m1, m2);

// EXPLANATION:
// - Both threads attempt to lock the SAME mutex set
// - std::lock() internally orders and retries locking
// - If one thread gets both locks, the other waits
// - Circular wait CANNOT occur
//
// RESULT: ✅ NO DEADLOCK


// -----------------------------------------------------
// [Example 1] --> NO DEADLOCK
// -----------------------------------------------------

// // Thread 1:
// std::lock(m1, m2);

// // Thread 2:
// std::lock(m2, m1);

// EXPLANATION:
// - Order of arguments does NOT matter
// - std::lock() ignores argument order internally
// - It guarantees atomic acquisition of all mutexes
//
// IMPORTANT INTERVIEW POINT:
// std::lock(m1, m2) == std::lock(m2, m1)
//
// RESULT: ✅ NO DEADLOCK


// -----------------------------------------------------
// [Example 2] --> NO DEADLOCK
// -----------------------------------------------------

// // Thread 1:
// std::lock(m1, m2, m3, m4);

// // Thread 2:
// std::lock(m3, m4);
// std::lock(m1, m2);

// EXPLANATION:
// - Thread 1 locks all 4 mutexes atomically
// - Thread 2 locks subsets using std::lock()
// - std::lock() releases already locked mutexes
//   if it fails to acquire all required locks
// - Circular wait is prevented
//
// RESULT: ✅ NO DEADLOCK


// [Example:3] --> YES, THIS CAN DEADLOCK
// //
// // Thread 1:
// std::lock(m1, m2);
// std::lock(m3, m4);

// // Thread 2:
// std::lock(m3, m4);
// std::lock(m1, m2);

// ----------------------------------------------------
// WHY THIS CAN DEADLOCK (IMPORTANT INTERVIEW POINT)
// ----------------------------------------------------
//
// std::lock() guarantees deadlock-free locking ONLY
// for the mutexes passed in THE SAME CALL.
//
// In this example:
//
// Thread 1 execution:
// - First acquires (m1, m2)
// - Then tries to acquire (m3, m4)
//
// Thread 2 execution:
// - First acquires (m3, m4)
// - Then tries to acquire (m1, m2)
//
// POSSIBLE EXECUTION SCENARIO:
//
// 1. Thread 1 locks (m1, m2)
// 2. Thread 2 locks (m3, m4)
// 3. Thread 1 waits for (m3, m4)  <-- held by Thread 2
// 4. Thread 2 waits for (m1, m2)  <-- held by Thread 1
//
// This creates a CIRCULAR WAIT:
//
// Thread 1 → waiting for Thread 2
// Thread 2 → waiting for Thread 1
//
// RESULT:
// - Neither thread can proceed
// - Neither thread releases its locks
// - Program enters DEADLOCK
//
// ----------------------------------------------------
// KEY INTERVIEW RULE (VERY IMPORTANT)
// ----------------------------------------------------
//
// ❗ std::lock() only prevents deadlock
// ❗ when ALL required mutexes are locked
// ❗ in ONE single std::lock() call
//
// Multiple std::lock() calls can still deadlock
// if different threads acquire different subsets first.
//
// ----------------------------------------------------
// HOW TO FIX THIS (DEADLOCK-FREE VERSION)
// ----------------------------------------------------
//
// Both threads should lock ALL mutexes together:
//
// std::lock(m1, m2, m3, m4);
//
// OR (Modern C++17):
//
// std::scoped_lock lock(m1, m2, m3, m4);
//
// ----------------------------------------------------
// ONE-LINE INTERVIEW ANSWER
// ----------------------------------------------------
//
// “std::lock prevents deadlock only within a single call;
// multiple std::lock calls across threads can still deadlock.”



// =====================================================
// FINAL INTERVIEW SUMMARY
// =====================================================
//
// std::lock() prevents deadlock ONLY when:
// - ALL required mutexes are passed in ONE std::lock() call
//
// Deadlock occurs when:
// - Mutexes are locked manually in different orders
//
// INTERVIEW ONE-LINER:
// “std::lock() guarantees deadlock-free locking only
//  for the mutexes passed in the same call.”
#include <iostream>
#include <thread>
#include <mutex>
std::mutex m1, m2;
void task_a() {
    while(1){
        //std::lock(m1, m2);
        m1.lock();
        m2.lock();
        // critical section
        std::cout << "Task A in critical section\n";
        m1.unlock();
        m2.unlock();
    }
}
void task_b() {
    while(1){
        //std::lock(m2, m1);
        // critical section
        m2.lock();
        m1.lock();
        std::cout << "Task B in critical section\n";
        m2.unlock();
        m1.unlock();
    }
}
int main() {
    std::thread t1(task_a);
    std::thread t2(task_b);
    t1.join();
    t2.join();
    return 0;
}