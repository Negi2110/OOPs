// # ✅ **Mutex Example — Explanation (One Paragraph)**

// This example demonstrates how a thread safely accesses a shared resource using a Windows mutex. A global mutex handle (`hMutex`) is created with `CreateMutex`, passing `FALSE` as the *acquire* argument so the mutex starts in an unlocked state. When the thread function `SyncThread` runs, it first calls `WaitForSingleObject(hMutex, INFINITE)`, which blocks until the thread successfully acquires the mutex. After entering the critical section (the protected code that accesses the shared resource), the thread calls `ReleaseMutex(hMutex)` to unlock the mutex and allow other waiting threads to continue. This ensures proper synchronization so that multiple threads do not access the resource at the same time, preventing race conditions.

// ---

// # ✅ **Mutex Example — Clean Code with Comments**

// ```cpp
char mutexName[] = "MUTEX1";
HANDLE hMutex;

// Thread function that accesses a shared resource
DWORD WINAPI SyncThread(LPVOID param) {

    // Wait forever until mutex becomes available
    WaitForSingleObject(hMutex, INFINITE);

    // ---- Protected Critical Section ----
    // Access shared resource here
    // ------------------------------------

    // Release mutex so other threads can proceed
    ReleaseMutex(hMutex);

    return 0;
}

int main() {

    DWORD threadId;
    HANDLE hdl;

    // Create mutex with:
    // NULL security attributes,
    // FALSE = do NOT acquire the mutex immediately,
    // name = "MUTEX1"
    hMutex = CreateMutex(NULL, FALSE, LPCWSTR(mutexName));

    // Create a thread that will use the mutex
    hdl = CreateThread(NULL, 0, SyncThread, NULL, 0, &threadId);

    // ... main thread continues

    return 0;
}
// ```

// ---

// # 🔍 Why `FALSE` in CreateMutex?

// Because passing:

// ```cpp
// CreateMutex(NULL, FALSE, ...);
// ```

// means:

// * The mutex is **not locked** immediately.
// * The **first call** to `WaitForSingleObject` gets ownership normally.
// * This avoids unexpected "already owned" behavior when the program starts.

// This is exactly why the slide says:

// > “The acquire argument is set to false to ensure the first call to WaitForSingleObject can gain control and lock the mutex.”

