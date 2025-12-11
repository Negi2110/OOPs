// Here is the **same Thread Example rewritten cleanly with full comments**, exactly matching your slide but improved for clarity and correctness (interview-ready + beginner-friendly).

// ---

// # ✅ **Thread Example (Fully Explained & Commented)**

// ```cpp
#include "stdafx.h"     // Precompiled header (Visual Studio projects)
#include <iostream>
#include <windows.h>    // REQUIRED for CreateThread, Sleep, HANDLE//because we are using Windows API

using namespace std;

/*
    Basic thread function.
    Must follow the signature: DWORD WINAPI FunctionName(LPVOID param)
*/
DWORD WINAPI BasicThread(LPVOID param) {

    cout << "Thread start \n";

    Sleep(2000);    // Pause this thread for 2 seconds (2000 ms)

    cout << "Thread end \n";

    return 0;       // Exit code of the thread
}

int main() {

    DWORD threadId;     // Will store the thread ID
    HANDLE hdl;         // Handle to the thread

    /*
        CreateThread parameters:
        1. NULL → default security attributes
        2. 0 → default stack size
        3. BasicThread → function the new thread will run
        4. NULL → no parameter passed to the thread
        5. 0 → start executing immediately
        6. &threadId → where to store the new thread’s ID
    */
    hdl = CreateThread(
            NULL,
            0,
            BasicThread,
            NULL,
            0,
            &threadId
        );

    system("pause");   // Keep console open to see output
    return 0;
}
// ```

// ---

// # 🧵 **What This Program Does**

// 1. The main program starts running.
// 2. `CreateThread()` is called.
// 3. A new thread starts executing the `BasicThread()` function.
// 4. The new thread prints:

//    ```
//    Thread start
//    ```
// 5. The thread sleeps for 2 seconds.
// 6. The thread prints:

//    ```
//    Thread end
//    ```
// 7. Meanwhile, the main thread waits for user input due to `system("pause")`.

// ---

// # 🔥 **Key Concepts This Example Demonstrates**

// * How to create a new Windows thread using `CreateThread()`
// * How to write a valid thread function (`DWORD WINAPI …`)
// * Thread runs independently from `main`
// * Console stays open until you press a key
// * Each thread has its own flow of execution

// ---

// # 📝 **One-Line Interview Summary**

// > “`CreateThread()` starts a new OS-level thread that runs a function independently from the main program, allowing true parallel execution on multi-core CPUs.”

// ---

