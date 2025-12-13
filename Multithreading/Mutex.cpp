// TOPIC: Mutex in C++ (Multithreading)
//
// WHY USE MUTEX?
// A mutex is used to synchronize access to shared resources and to prevent race conditions
// when multiple threads attempt to read or modify shared data at the same time.


// RACE CONDITION:
//
// 0. A race condition is a situation where two or more threads or processes try to
//    access and modify a shared (common) resource simultaneously.
// 1. If a race condition occurs, the program behavior becomes unpredictable and incorrect.
// 2. To prevent a race condition, the shared code must be protected.
// 3. The protected part of the code is called the Critical Section or Critical Region.


// MUTEX:
//
// 0. Mutex stands for Mutual Exclusion.
// 1. A mutex is used to avoid race conditions by allowing only one thread at a time
//    to enter the critical section.
// 2. We use lock() to acquire the mutex before accessing the shared resource.
// 3. We use unlock() to release the mutex after finishing with the shared resource.
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int myAmount=0; // Shared resource
std::mutex m; // Mutex for critical section
void addMoney() {
    m.lock(); // Acquire the mutex before entering critical section
    ++myAmount; // Increment the shared resource//critical section
    m.unlock(); // Release the mutex after leaving critical section
}

int main() {
    std::thread t1(addMoney); // Create thread 1
    std::thread t2(addMoney); // Create thread 2

    t1.join(); // Wait for thread 1 to finish
    t2.join(); // Wait for thread 2 to finish

    cout << "Final amount: " << myAmount << endl;
    return 0; // Return 0 to indicate successful execution
}


// =============================================================
// Interview Q&A: Mutex & Critical Section
// =============================================================


// Q1. What is a race condition?
//
// Answer:
// A race condition occurs when two or more threads access and modify shared
// data simultaneously, and the final result depends on the order of execution.
// This leads to unpredictable and incorrect program behavior.

// A race condition occurs when two or more threads
// concurrently access shared data AND
// at least one of them modifies the data,
// and the final result depends on the execution order.
//
// Q2. What is a critical section?
//
// Answer:
// A critical section is a part of the code that accesses shared resources
// and must not be executed by more than one thread at a time.
// Protecting this section prevents race conditions.


// Q3. What is a mutex?
//
// Answer:
// A mutex (Mutual Exclusion) is a synchronization mechanism that ensures
// only one thread can enter a critical section at any given time,
// thereby preventing race conditions.


// Q4. Why do we need a mutex if we already have a critical section?
//
// Answer:
// A critical section is a concept, while a mutex is a tool used to enforce
// that concept. Mutexes provide the actual mechanism to lock and unlock
// access to critical sections.


// Q5. How does a mutex prevent race conditions?
//
// Answer:
// A mutex allows only one thread to lock it at a time.
// Other threads attempting to lock the mutex are blocked until it is released,
// ensuring serialized access to shared resources.


// Q6. What happens if two threads try to lock the same mutex?
//
// Answer:
// The first thread acquires the mutex and enters the critical section.
// The second thread is blocked until the mutex is released by the first thread.


// Q7. What happens if a thread forgets to unlock a mutex?
//
// Answer:
// Other threads will remain blocked indefinitely,
// leading to a deadlock or application freeze.


// Q8. Difference between mutex and critical section?
//
// Answer:
// A critical section is the region of code that needs protection,
// while a mutex is the synchronization primitive used to protect that region.


// Q9. Can a mutex be used across processes?
//
// Answer:
// Yes. Named mutexes can be shared across multiple processes,
// while unnamed mutexes are limited to the same process.


// Q10. What is deadlock?
//
// Answer:
// A deadlock occurs when two or more threads wait indefinitely for each other
// to release resources, resulting in a complete standstill.


// Q11. Can a mutex cause performance issues?
//
// Answer:
// Yes. Excessive locking, long critical sections, or frequent context switching
// can reduce performance.


// Q12. When should you NOT use a mutex?
//
// Answer:
// Avoid mutexes for:
// - Read-only shared data
// - Very small atomic operations (use atomic variables instead)
// - Performance-critical paths where lock-free solutions are preferable


// Q13. How is mutex used in C++ (basic syntax)?
//
// Example:
//
// std::mutex m;
//
// m.lock();
// // critical section
// m.unlock();


// Q14. What is RAII in mutex usage?
//
// Answer:
// RAII (Resource Acquisition Is Initialization) ensures a mutex is
// automatically unlocked when it goes out of scope, preventing deadlocks.
//
// Example:
//
// std::lock_guard<std::mutex> lock(m);
// // critical section


// Q15. Mutex vs Semaphore (quick answer)?
//
// Answer:
// A mutex allows only one thread at a time to access a resource,
// while a semaphore allows a limited number of threads to access a resource.


// =============================================================
// One-Line Interview Summary
// =============================================================
//
// A mutex enforces mutual exclusion to protect critical sections
// and prevent race conditions in multithreaded programs.

// Term	Meaning
// Data Race	Two threads access same memory concurrently AND at least one write occurs without synchronization
// Race Condition	Program correctness depends on timing/order of thread execution

// 📌 All data races are race conditions, but not all race conditions are data races.

// 🧠 Interview One-Liner (Perfect Answer)

// “If multiple threads only read shared data, there is no race condition.
// A race condition requires at least one thread to modify shared data.”

// ✍️ Final Comment-Ready Version
// NOTE:
// If multiple threads ONLY READ shared data and do not modify it,
// then no race condition occurs.
//
// A race condition requires:
// 1. Shared data
// 2. Concurrent access
// 3. At least ONE write operation
// 4. No proper synchronization
// =============================================================
// END OF FILE
// =============================================================