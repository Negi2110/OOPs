// ## ✅ Producer–Consumer Using Binary Semaphores (C++20)

// ### Fully Commented Code

// ```cpp
#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std;
using namespace std::chrono;

/*
 Two binary semaphores are used for synchronization:

 signal_to_producer:
   - Controls when producer is allowed to produce
   - Initialized to 1 → producer can start immediately

 signal_to_consumer:
   - Controls when consumer is allowed to consume
   - Initialized to 0 → consumer waits initially
*/
std::binary_semaphore 
signal_to_producer{1},   // producer allowed initially
signal_to_consumer{0};   // consumer blocked initially

/*
 Shared buffer size and buffer itself
*/
#define buff_size 5
int buff[buff_size];

/*
 Producer function:
 ------------------
 Produces data and places it into the shared buffer.
 Uses semaphore to ensure producer and consumer
 do not access buffer at the same time.
*/
void producer() {
    while (1) {

        /*
         Wait until producer is allowed to produce.
         acquire() blocks if semaphore count is 0.
        */
        signal_to_producer.acquire();

        cout << "Produced = ";

        /*
         Fill the buffer with data.
         This is the producer's "work".
        */
        for (int i = 0; i < buff_size; ++i) {
            buff[i] = i * i;        // Produce data
            cout << buff[i] << " ";
            cout << flush;

            // Simulate production time
            this_thread::sleep_for(milliseconds(200));
        }

        cout << endl;

        /*
         Signal the consumer that data is ready.
        */
        signal_to_consumer.release();
    }
}

/*
 Consumer function:
 ------------------
 Consumes data from the shared buffer.
 Waits until producer signals that data is available.
*/
void consumer() {
    while (1) {

        /*
         Wait until consumer is allowed to consume.
        */
        signal_to_consumer.acquire();

        cout << "Consumed = ";

        /*
         Read data from buffer in reverse order
         and clear buffer values.
        */
        for (int i = buff_size - 1; i >= 0; --i) {
            cout << buff[i] << " ";
            cout << flush;

            buff[i] = 0;   // Consume data

            // Simulate consumption time
            this_thread::sleep_for(milliseconds(200));
        }

        cout << endl << endl;

        /*
         Signal producer that buffer is free
         and it can produce again.releasing means incrementing 
        */
        signal_to_producer.release();
    }
}

int main()
{
    /*
     Create producer and consumer threads.
     Both start execution immediately.
    */
    thread producer_thread(producer);
    thread consumer_thread(consumer);

    /*
     Main thread does not participate in synchronization.
     It simply waits for child threads.
    */
    cout << "[main] Got the signal\n";

    producer_thread.join();
    consumer_thread.join();

    return 0;
}

// ## 🧠 What This Code Demonstrates (Interview Perspective)

// ### ✔ Producer–Consumer Problem

// * One thread **produces data**
// * One thread **consumes data**
// * Shared buffer must not be accessed simultaneously

// ### ✔ Binary Semaphores

// * `signal_to_producer` → controls producer execution
// * `signal_to_consumer` → controls consumer execution
// * Perfect example of **thread signaling**

// ### ✔ No Busy Waiting

// * Threads block using `acquire()`
// * CPU is not wasted

// ---

// ## 🔄 Execution Flow (Very Important)

// 1. Producer starts first (`signal_to_producer = 1`)
// 2. Producer fills buffer
// 3. Producer signals consumer
// 4. Consumer reads buffer
// 5. Consumer signals producer
// 6. Cycle repeats forever

// ---

// ## ⚠ Important Interview Notes

// * `std::binary_semaphore` requires **C++20**
// * If C++20 is not available → use `condition_variable`
// * Semaphores are used for **coordination**, not data protection
// * Mutex would be needed if **multiple producers/consumers** existed

// ---

// ## ✅ One-Line Interview Explanation

// > *“This program solves the producer–consumer problem using binary semaphores, ensuring strict alternation between producer and consumer without race conditions.”*

// ---

// ## 🎯 Extra Credit (Say This to Impress)

// > *“Binary semaphores are ideal for signaling between threads, while mutexes are better suited for protecting shared data.”*
