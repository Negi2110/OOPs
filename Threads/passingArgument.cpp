// # ✅ **Passing Arguments to a Thread — Explanation (One Paragraph)**

// When using `CreateThread()` in Windows, the only way to pass data to the new thread is through the `LPVOID param` parameter. Since `LPVOID` is just a generic void pointer, you must **cast your data to `LPVOID` before passing it**, and then **cast it back to the correct type inside the thread function**. This allows you to send objects, integers, structs, or any custom data to a thread. Once inside the thread, the typed pointer can be used normally to call member functions and access data.

// ---

// # 🧵 **Thread Function Example (from Slide, Clean & Commented)**

// ```cpp
// DWORD WINAPI BasicThread(LPVOID param) {

//     // Cast back the void pointer to the correct type
//     GameObject* obj = (GameObject*)param;

//     // Now you can call member functions of GameObject
//     // obj->Run();
//     // obj->Update();

//     return 0;
// }
// ```

// ---

// # 🧩 **Passing an Argument When Creating the Thread**

// ```cpp
#include<iostream>
#include<windows.h>
class GameObject {
    // GameObject members and methods would go here
};  
int main() {

    DWORD threadId;
    HANDLE hdl;

    GameObject* obj = new GameObject();   // Object to pass to thread

    // Pass obj as LPVOID
    hdl = CreateThread(
            NULL,
            0,
            BasicThread,     // Thread callback
            (LPVOID)obj,     // <-- Passing the object
            0,
            &threadId
        );

    return 0;
}
// ```

// ---

// # 🔥 **What’s Happening Here**

// ### 1. Convert object pointer → LPVOID:

// ```cpp
// (LPVOID)obj
// ```

// ### 2. Thread receives it as:

// ```cpp
// LPVOID param
// ```

// ### 3. Convert back inside the thread:

// ```cpp
// GameObject* obj = (GameObject*)param;
// ```

// Now `obj` is a fully typed pointer again and can be used normally.

// ---

// # ⭐ **Important Notes**

// * Windows requires thread arguments to be `LPVOID` for compatibility.
// * You can pass:

//   * Objects
//   * Structs
//   * Arrays
//   * Integers (cast with care)
// * This works because **pointers are just memory addresses**.
// * Inside the thread you **must cast back to the correct type** or your program will crash.

// ---

// # 📝 **One-line Interview Summary**

// > “Arguments are passed to Windows threads by casting them to `LPVOID`, and inside the thread they must be cast back to their original type.”

