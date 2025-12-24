// ======================================================
// TOPIC: Producer–Consumer Problem (Bounded Buffer)
// ======================================================
//
// PROBLEM OVERVIEW:
// Producer–Consumer is a classic synchronization problem
// where:
//
// - One or more PRODUCER threads generate data
// - One or more CONSUMER threads consume that data
// - Both share a COMMON BUFFER
//
// ------------------------------------------------------
// WHY SYNCHRONIZATION IS REQUIRED
// ------------------------------------------------------
//
// 1. Producer must NOT produce when the buffer is FULL
// 2. Consumer must NOT consume when the buffer is EMPTY
// 3. Access to the buffer must be MUTUALLY EXCLUSIVE
// 4. Threads must COORDINATE their execution
//
// ------------------------------------------------------
// TOOLS USED (C++ INTERVIEW STANDARD)
// ------------------------------------------------------
//
// - std::mutex
//     → Protects the shared buffer (critical section)
//
// - std::condition_variable
//     → Allows threads to wait and notify each other
//
// IMPORTANT:
// - condition_variable ALWAYS works with a mutex
// - wait() atomically releases the mutex and suspends thread
//
// ------------------------------------------------------
// PRODUCER THREAD LOGIC
// ------------------------------------------------------
//
// 1. Lock the mutex
// 2. Check if buffer is FULL
//    - If FULL → wait on condition_variable
//    - wait() releases mutex and blocks the thread
// 3. When notified and buffer has space:
//    - Produce item
//    - Insert item into buffer
// 4. Unlock the mutex
// 5. Notify CONSUMER that data is available
//
// ------------------------------------------------------
// CONSUMER THREAD LOGIC
// ------------------------------------------------------
//
// 1. Lock the mutex
// 2. Check if buffer is EMPTY
//    - If EMPTY → wait on condition_variable
//    - wait() releases mutex and blocks the thread
// 3. When notified and buffer has data:
//    - Remove item from buffer
//    - Consume item
// 4. Unlock the mutex
// 5. Notify PRODUCER that space is available
//
// ------------------------------------------------------
// IMPORTANT INTERVIEW POINTS
// ------------------------------------------------------
//
// 1. Mutex ensures MUTUAL EXCLUSION
// 2. Condition variable ensures COORDINATION
// 3. Producer and Consumer MUST notify each other
// 4. Always use wait() with a CONDITION (predicate)
//    to handle spurious wakeups
//
// ------------------------------------------------------
// WHY THIS PROBLEM IS IMPORTANT
// ------------------------------------------------------
//
// - Demonstrates thread synchronization
// - Shows correct use of mutex + condition_variable
// - Prevents race conditions
// - Prevents busy waiting
//
// ------------------------------------------------------
// ONE-LINE INTERVIEW ANSWER
// ------------------------------------------------------
//
// “Producer–Consumer is a synchronization problem where
// producer threads generate data and consumer threads
// consume it using mutex and condition_variable to ensure
// safe and coordinated access to a shared buffer.”

// ❌ WRONG: Using sleep() instead of condition_variable
// ❌ WRONG: Accessing buffer without mutex
// ✅ CORRECT: mutex + condition_variable + predicate

// ======================================================
// PRODUCER–CONSUMER PROBLEM USING condition_variable
// ======================================================
//
// Shared resources:
// - buffer        → shared queue (critical section)
// - mu            → mutex protecting buffer
// - cond          → condition variable for coordination
//
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
std::condition_variable cond;
std::deque<int> buffer;
std::mutex mu;
const unsigned int maxBufferSize = 50;

// ------------------------------------------------------
// PRODUCER FUNCTION
// ------------------------------------------------------
//
// - Produces values and pushes them into the buffer
// - Stops when val becomes 0
//
void producer(int val) {

    // Produce until val becomes 0
    while (val) {

        // unique_lock is REQUIRED with condition_variable
        // because wait() needs to unlock & relock mutex
        std::unique_lock<std::mutex> locker(mu);

        // WAIT until buffer has space
        //
        // - Releases mutex while waiting
        // - Reacquires mutex when notified
        // - Predicate protects against spurious wakeups
        //
        cond.wait(locker, []() {
            return buffer.size() < maxBufferSize;
        });

        // ---- CRITICAL SECTION START ----
        buffer.push_back(val);
        std::cout << "Produced: " << val << std::endl;
        --val;
        // ---- CRITICAL SECTION END ----

        // Explicit unlock (optional but improves performance)
        locker.unlock();

        // Notify ONE waiting consumer thread
        cond.notify_one();
    }
}

// ------------------------------------------------------
// CONSUMER FUNCTION
// ------------------------------------------------------
//
// - Consumes values from buffer
// - Runs indefinitely
//
void consumer() {

    while (true) {

        std::unique_lock<std::mutex> locker(mu);

        // WAIT until buffer has data
        //
        // - If buffer empty → wait
        // - Mutex is released during wait
        //
        cond.wait(locker, []() {
            return buffer.size() > 0;
        });

        // ---- CRITICAL SECTION START ----
        int val = buffer.back();
        buffer.pop_back();
        std::cout << "Consumed: " << val << std::endl;
        // ---- CRITICAL SECTION END ----

        locker.unlock();

        // Notify producer that space is available
        cond.notify_one();
    }
}

// ------------------------------------------------------
// MAIN FUNCTION
// ------------------------------------------------------
int main() {

    // One producer, one consumer
    std::thread t1(producer, 100);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
// ```

// ---

// ## 🔑 **IMPORTANT INTERVIEW TAKEAWAYS**

// ```cpp
// 1. mutex protects shared data (buffer)
// 2. condition_variable coordinates producer & consumer
// 3. wait() ALWAYS releases the mutex atomically
// 4. Predicate prevents spurious wakeups
// 5. notify_one() wakes exactly one waiting thread


// ## ❗ Why `unique_lock` and NOT `lock_guard`?


// lock_guard:
// - Cannot be unlocked manually
// - Cannot be used with condition_variable
//
// unique_lock:
// - Can be unlocked/relocked
// - REQUIRED for cond.wait()

// ❌ Using sleep() instead of condition_variable
// ❌ Accessing buffer without mutex
// ❌ Using if instead of while in wait()
// ❌ Forgetting predicate in wait()

// ## ⭐ One-Line Interview Answer

// > **“Producer–Consumer uses mutex for mutual exclusion and condition_variable for coordination so producers wait when buffer is full and consumers wait when it’s empty.”**

//it is random as it epends on cpu which thread is able to acquire the lock again and again ..you run every time it will give different result

//he output stops because the consumer waits forever on the condition variable after the producer exits without notifying.”