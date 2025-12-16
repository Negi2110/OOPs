#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// =============================================================
// Two mutexes representing shared resources
// =============================================================
std::mutex m1;
std::mutex m2;

// =============================================================
// Thread 1 function
// =============================================================
void thread1() {

    // Thread 1 locks m1 first
    m1.lock();
    //std::this_thread::sleep_for(std::chrono::seconds(2)); // Added to increase chance of deadlock
    // Context switch may happen here --------------------------
    // Thread 2 may start executing and lock m2
    // ---------------------------------------------------------

    // Thread 1 tries to lock m2
    m2.lock();

    // CRITICAL SECTION (may never be reached)
    cout << "Critical Section of Thread 1" << endl;

    m2.unlock();
    m1.unlock();
}

// =============================================================
// Thread 2 function
// =============================================================
void thread2() {

    // Thread 2 locks m2 first
    m2.lock();
   // std::this_thread::sleep_for(std::chrono::seconds(2)); // Added to increase chance of deadlock
    // Context switch may happen here --------------------------
    // Thread 1 may already hold m1
    // ---------------------------------------------------------

    // Thread 2 tries to lock m1
    m1.lock();

    // CRITICAL SECTION (may never be reached)
    cout << "Critical Section of Thread 2" << endl;

    m1.unlock();
    m2.unlock();
}

// =============================================================
// Main function
// =============================================================
int main() {

    // Two threads running concurrently
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}

//there is possiblity dealock not come in 1000the of time but it can come any time when thread scheduling happens in certain way

// 🚨 What problem does this code have?
// ❌ DEADLOCK
// 🧠 How deadlock happens (step-by-step)
// Thread 1               Thread 2
// --------               --------
// locks m1               locks m2
// waits for m2           waits for m1


// ✔ Thread 1 holds m1 and waits for m2
// ✔ Thread 2 holds m2 and waits for m1

// 👉 Both threads wait forever
// 👉 No progress
// 👉 Program hangs

// 🔥 Deadlock Conditions (INTERVIEW MUST-KNOW)

// All four must be true:

// Mutual Exclusion – mutex allows only one owner

// Hold and Wait – thread holds one lock and waits for another

// No Preemption – mutex cannot be forcibly taken

// Circular Wait – thread1 → thread2 → thread1

// ✔ Your code satisfies ALL FOUR

// ❓ Why is this code dangerous?

// Execution order is unpredictable

// Deadlock may or may not happen

// Extremely hard to debug in production

// Program may freeze randomly

// ✅ How to FIX this deadlock (Interview Gold)
// ✔ Solution 1: Lock mutexes in SAME ORDER
// void thread1() {
//     m1.lock();
//     m2.lock();
//     cout << "Thread 1" << endl;
//     m2.unlock();
//     m1.unlock();
// }

// void thread2() {
//     m1.lock();   // SAME ORDER
//     m2.lock();
//     cout << "Thread 2" << endl;
//     m2.unlock();
//     m1.unlock();
// }

// ✔ Solution 2: Use std::lock (BEST PRACTICE)
// void threadSafe() {
//     std::lock(m1, m2);   // deadlock-free
//     std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
//     std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
//     cout << "Critical Section" << endl;
// }

// ✔ Solution 3: Use std::scoped_lock (C++17+)
// void threadSafe() {
//     std::scoped_lock lock(m1, m2);
//     cout << "Critical Section" << endl;
// }

// ✍️ Interview-ready comment summary
// // This program demonstrates DEADLOCK.
// // Deadlock occurs when two threads lock resources
// // in different orders and wait for each other forever.
// //
// // Fix:
// // - Always lock mutexes in the same order
// // - OR use std::lock / std::scoped_lock

// ⭐ Perfect Interview One-Liner

// “This code can cause deadlock because threads acquire mutexes in different orders, leading to circular wait.”


// ## ✅ Short, precise answer

// > **In your case, `m1` and `m2` are the resources.**

// The mutexes themselves represent **exclusive access to shared resources**.

// ---

// ## 🧠 Why mutex is considered a resource

// In operating systems and concurrency theory:

// > A **resource** is *anything that must be accessed exclusively*.

// Examples:

// * CPU
// * Memory
// * File
// * Network socket
// * Database connection
// * **Mutex / lock**

// So yes — **a mutex itself is a resource**.

// ---

// ## 🔍 In YOUR code

// ```cpp
// std::mutex m1;
// std::mutex m2;
// ```

// These represent two exclusive resources.

// ### Thread behavior:

// ```cpp
// // Thread 1
// m1.lock();  // acquires resource m1
// m2.lock();  // requests resource m2

// // Thread 2
// m2.lock();  // acquires resource m2
// m1.lock();  // requests resource m1
// ```

// ---

// ## 🔄 Mapping your code to deadlock theory

// ### 1️⃣ Mutual Exclusion

// ```cpp
// m1.lock();
// ```

// * Only one thread can own `m1`
// * ✔ Condition satisfied

// ---

// ### 2️⃣ Hold and Wait

// ```cpp
// // Thread 1
// m1.lock();  // holding m1
// m2.lock();  // waiting for m2
// ```

// * Thread holds one resource and waits for another
// * ✔ Condition satisfied

// ---

// ### 3️⃣ No Preemption

// ```cpp
// // Thread 2 cannot force Thread 1 to unlock m1
// ```

// * Mutex cannot be forcibly taken
// * ✔ Condition satisfied

// ---

// ### 4️⃣ Circular Wait

// ```text
// Thread 1 → waiting for m2 (held by Thread 2)
// Thread 2 → waiting for m1 (held by Thread 1)
// ```

// * Circular dependency exists
// * ✔ Condition satisfied

// ---

// ## 🧠 Important interview clarification

// > The **mutex represents the permission to access the real resource**
// > (e.g., shared data, file, or critical section).

// Even if your code doesn’t modify data:

// * The **lock itself is still a resource**
// * Threads are competing for that resource

// ---

// ## ✍️ Interview-ready comment explanation

// ```cpp
// // In this program, the mutexes (m1 and m2) are the resources.
// // Each mutex represents exclusive access to a critical section.
// //
// // Deadlock occurs because threads acquire these resources
// // in different orders, creating a circular wait.
// ```

// ---

// ## ⭐ Perfect interview one-liner

// > **“Yes, in this case the mutex itself is the resource, and deadlock occurs because threads compete for mutex ownership in a circular manner.”**

