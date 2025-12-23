
#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std;

/*
 MyPrinter class:
 ----------------
 This class prints a string using multiple threads.
 Each thread prints a fixed number of characters in
 a round-robin order using condition variables.
*/
class MyPrinter {
private:
    string str;                      // Input string to be printed
    int char_count;                  // Number of characters per print
    int thread_count;                // Total number of threads

    vector<thread> threads;          // Stores thread objects
    vector<std::thread::id> thread_ids; // Stores thread IDs for ordering

    int thread_id;                   // (Unused) logical thread id
    int allowed_thread;              // Index of thread allowed to print
    int next_char;                   // Index of next character to print

    mutex mutex_lock;                // Mutex for synchronization
    condition_variable cv;           // Condition variable for thread coordination

public:

    /*
     Constructor:
     Initializes all class variables.
    */
    MyPrinter(string s, int c_count, int t_count) {
        str = s;
        char_count = c_count;
        thread_count = t_count;
        thread_id = 0;
        next_char = 0;
        allowed_thread = 0;
    }

    /*
     Returns the logical index of the current thread
     by matching thread ID from thread_ids vector.
    */
    int getCurrentThreadId(const std::thread::id& id) {
        int thread_id = 0;
        for (auto& e : thread_ids) {
            if (e == id)
                return thread_id;
            thread_id++;
        }
        return -1;  // Should not happen
    }

    /*
     Creates and starts all threads.
    */
    void run() {

        for (int i = 0; i < thread_count; i++) {

            // Create a thread that runs print_thread()
            thread t(&MyPrinter::print_thread, this);

            // Print OS-level thread ID
            cout << "Thread " << t.get_id() << " is " << i << endl;

            // Store thread ID for ordered execution
            thread_ids.push_back(t.get_id());

            // Move thread into vector
            threads.push_back(move(t));
        }

        // Wait for all threads to complete
        for (int i = 0; i < thread_count; i++) {
            threads[i].join();
        }
    }

    /*
     Busy-wait function:
     Ensures that all threads are created before printing starts.
    */
    void waitforallthreadinit() {
        while (true) {
            if (thread_count == thread_ids.size())
                return;
        }
    }

    /*
     Thread execution function:
     Ensures threads print in round-robin order using
     mutex and condition variable.
    */
    void print_thread() {

        while (true) {

            // Ensure all threads are initialized
            waitforallthreadinit();

            // Artificial delay (for visibility)
            this_thread::sleep_for(chrono::milliseconds(1000));

            // Lock mutex before accessing shared data
            unique_lock<mutex> lock(mutex_lock);

            /*
             Wait until this thread is the allowed thread.
             Condition variable ensures ordered execution.
            */
            cv.wait(lock, [this] {
                return std::this_thread::get_id() == thread_ids[allowed_thread];
            });

            // Print characters
            print_chars();

            // Move to next allowed thread
            allowed_thread++;
            if (allowed_thread == thread_count)
                allowed_thread = 0;

            // Wrap around string index if needed
            if (next_char >= str.length())
                next_char -= str.length();

            // Unlock mutex
            lock.unlock();

            // Notify all waiting threads
            cv.notify_all();
        }
    }

    /*
     Prints a chunk of the string starting from next_char.
    */
    void print_chars() {

        // Print logical thread ID
        cout << "ThreadId "
             << getCurrentThreadId(std::this_thread::get_id())
             << " : ";

        int printcount = 0;

        /*
         Print characters until either:
         - char_count reached
         - end of string reached
        */
        for (int i = next_char;
             i < str.length() && printcount < char_count;
             i++) {

            cout << str[i];
            printcount++;
        }

        /*
         If end of string is reached before char_count,
         wrap around and continue printing from start.
        */
        if (printcount < char_count) {
            for (int i = 0; i < char_count - printcount; i++) {
                cout << str[i];
            }
        }

        // Move index forward
        next_char = next_char + char_count;

        cout << endl;
    }
};

int main(int argc, char *argv[]) {

    /*
     Validate command-line arguments.
     Expected:
     1) string
     2) character count
     3) thread count
    */
    if (argc != 4) {
        cout << "Please provide 3 arguments - "
             << "a string, char count & thread count"
             << endl;
        return 1;
    }

    // Read inputs
    string str = argv[1];
    int char_count = atoi(argv[2]);
    int thread_count = atoi(argv[3]);

    // Create printer object
    MyPrinter p(str, char_count, thread_count);

    // Start printing using threads
    p.run();

    return 0;
}
// ```

// ---

// ## 🧠 Interview Notes (Very Important)

// ✔ Uses **mutex + condition_variable** for ordered execution
// ✔ Demonstrates **round-robin thread scheduling**
// ✔ Prevents race conditions on shared variables
// ✔ Shows advanced **thread coordination logic**

// ⚠ Improvements you can mention:

// * Replace busy-wait with condition variable
// * Add exit condition for infinite loop
// * Avoid `sleep_for` in production code

// ---

// ## ✅ One-Line Interview Explanation

// > *“This program uses condition variables and mutexes to coordinate multiple threads so they print fixed-size chunks of a string in a strict round-robin order.”*

// ---
