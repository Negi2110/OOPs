// # ✅ **What `SetThreadPriority()` Does**

// `SetThreadPriority()` changes the scheduling priority of an existing thread.
// Higher priority threads get more CPU time; lower priority threads get less.

// ### ✔ Function Prototype

// ```cpp
// BOOL SetThreadPriority(HANDLE hThread, int nPriority);
// ```

// ### ✔ Parameters

// * **hThread** → The thread handle returned from `CreateThread()`
// * **nPriority** → One of the predefined priority constants:

// ```
// THREAD_PRIORITY_TIME_CRITICAL    15
// THREAD_PRIORITY_HIGHEST          2
// THREAD_PRIORITY_ABOVE_NORMAL     1
// THREAD_PRIORITY_NORMAL           0
// THREAD_PRIORITY_BELOW_NORMAL    -1
// THREAD_PRIORITY_LOWEST          -2
// THREAD_PRIORITY_IDLE            -15
// ```

// ### ✔ Returns   

// * **Non-zero** → success
// * **Zero** → failure (use `GetLastError()` to diagnose)

// ---

// # 🧵 **Complete Working Example with Comments**

// ```cpp
#include <iostream>
#include <windows.h>
using namespace std;

// Thread function
DWORD WINAPI MyThreadFunction(LPVOID param) {
    while (true) {
        cout << "Running thread...\n";
        Sleep(500);
    }
    return 0;
}

int main() {

    DWORD threadId;
    HANDLE hThread;

    // Create a new thread
    hThread = CreateThread(
        NULL,               // default security
        0,                  // default stack
        MyThreadFunction,   // thread function
        NULL,               // parameter to thread function
        0,                  // run immediately
        &threadId
    );

    if (hThread == NULL) {
        cout << "Thread creation failed!\n";
        return 1;
    }

    // Set thread priority to highest
    if (SetThreadPriority(hThread, THREAD_PRIORITY_HIGHEST)) {
        cout << "Thread priority set to HIGHEST\n";
    } else {
        cout << "Failed to set thread priority. Error: " 
             << GetLastError() << endl;
    }

    // Prevent program from closing
    system("pause");
    return 0;
}
// ```

// ---

// # 🔥 **What This Code Does**

// * Creates a thread that prints messages continuously.
// * Sets the thread’s priority to **THREAD_PRIORITY_HIGHEST**.
// * Thread will run more frequently than normal priority threads.

// ---

// # ⚠️ Important Notes

// * Use high priorities carefully — they can **starve other threads**.
// * Avoid `THREAD_PRIORITY_TIME_CRITICAL` unless absolutely necessary.
// * Threads with very high priority can freeze the system UI.

// ---

// # 📝 One-Line Interview Summary

// > “`SetThreadPriority()` adjusts a thread’s scheduling priority, allowing time-critical tasks to run more often, but must be used carefully to avoid starving other threads.”

