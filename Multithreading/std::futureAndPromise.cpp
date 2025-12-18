// ## 📚 Example Code: Using std::future and std::promise in C++ Threading
// // ======================================================
// // TOPIC: std::future and std::promise in C++ Threading
// // ======================================================
// //
// // PURPOSE (Interview Perspective):
// // - Used for communication between threads
// // - One thread PRODUCES a value (std::promise)
// // - Another thread CONSUMES the value (std::future)
// //
// // KEY IDEA:
// // promise  ---> sets the value
// // future   ---> gets the value (and waits if needed)
// //
// // ------------------------------------------------------
// // REAL-WORLD ANALOGY:
// // promise = delivery person (will deliver result later)
// // future  = customer (waits for the delivery)
// // ------------------------------------------------------

// #include <iostream>
// #include <thread>
// #include <future>
// using namespace std;

// typedef unsigned long long ull;

// // ------------------------------------------------------
// // WORKER FUNCTION (Producer Thread)
// // ------------------------------------------------------
// //
// // - Receives a promise by reference
// // - Computes sum of odd numbers
// // - Sets the result into the promise
// //
// // IMPORTANT:
// // - promise MUST be passed by reference
// // - set_value() can be called ONLY ONCE
// //
#include <iostream>
#include <thread>
#include <future>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef long int ull;
void findOdd(std::promise<ull>&& OddSumPromise, ull start, ull end) {

    ull OddSum = 0;

    for (ull i = start; i <= end; ++i) {
        if (i & 1) {              // check if number is odd
            OddSum += i;
        }
    }

    // Store the result in the promise
    OddSumPromise.set_value(OddSum);

    // After this, future.get() will be unblocked
}

// ------------------------------------------------------
// MAIN FUNCTION (Consumer Thread)
// ------------------------------------------------------
int main() {
    ull Start = 0, end = 1900000000;
    // Step 1: Create a promise object
    std::promise<ull> OddSumPromise;

    // Step 2: Get future from promise
    // - future is linked to the promise
    // - it will receive the value set by promise
    std::future<ull> OddSumFuture = OddSumPromise.get_future();
    cout<<"thread created"<<endl;   
    // Step 3: Start a new thread and pass the promise
    std::thread t1(findOdd, std::move(OddSumPromise), Start, end);
    cout<<"waiting for result"<<endl;   
    // Step 4: future.get()
    //
    // - BLOCKS the calling thread
    // - waits until promise.set_value() is called
    // - retrieves the computed result
    //
    ull result = OddSumFuture.get();

    cout << "Sum of odd numbers: " << result << endl;

    t1.join();

    return 0;
}
// ```

// ---

// ## 🔑 **IMPORTANT INTERVIEW POINTS**

// ```cpp
// // 1. std::promise is used to SET a value from a thread
// // 2. std::future is used to GET the value in another thread
// // 3. future.get() blocks until the value is available
// // 4. set_value() can be called only once
// // 5. promise must be moved (std::move) into the thread
// ```

// ---

// ## ❗ Common Interview Traps

// ```cpp
// // ❌ Calling get_future() more than once → EXCEPTION
// // ❌ Calling set_value() twice → EXCEPTION
// // ❌ Forgetting to set value → future.get() blocks forever
// ```

// ---

// ## 🆚 future / promise vs mutex / condition_variable

// ```cpp
// // mutex + condition_variable:
// // - Used for synchronization and shared state
// // - More complex, error-prone
// //
// // future + promise:
// // - Used for one-time result transfer
// // - Cleaner and safer
// ```

// ---

// ## ⭐ One-Line Interview Answer

// > **“std::promise sets a value in one thread, and std::future retrieves it in another thread, blocking until the value is available.”**

