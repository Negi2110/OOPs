// // ============================
// // TOPIC: enum in C++
// // ============================
// //
// // enum (enumeration) is a user-defined data type
// // used to represent a set of named integral constants.
// //
// // WHY enum IS USED (Interview Perspective):
// // 1. Improves code readability (meaningful names instead of magic numbers)
// // 2. Prevents invalid values
// // 3. Makes code easier to maintain
// // 4. Commonly used for states, modes, flags, status codes
// //
// // EXAMPLE USE CASES:
// // - Days of week
// // - States of a thread (RUNNING, WAITING, BLOCKED)
// // - Menu options
// // - Error codes
// ```

// ---

// ### ✅ **Basic enum example**

// ```cpp
// #include <iostream>
// using namespace std;

// // Defining an enum
// enum Color {
//     RED,    // 0
//     GREEN,  // 1
//     BLUE    // 2
// };

// int main() {
//     Color c = RED;

//     if (c == RED) {
//         cout << "Color is RED" << endl;
//     }

//     return 0;
// }
// ```

// ```cpp
// // NOTES:
// // - enum values are stored as integers internally
// // - By default, first value = 0, then increments by 1
// ```

// ---

// ### ✅ **Enum with custom values**

// ```cpp
// enum ErrorCode {
//     SUCCESS = 0,
//     FILE_NOT_FOUND = 404,
//     SERVER_ERROR = 500
// };
// ```

// ```cpp
// // Interview Point:
// // enum allows assigning explicit integer values
// ```

// ---

// ### ❌ **Problem with traditional enum**

// ```cpp
// enum Status { OK, FAIL };
// enum Result { PASS, FAIL }; // ❌ Name conflict
// ```

// ```cpp
// // ISSUE:
// // - Traditional enums pollute global scope
// // - Can cause name conflicts
// ```

// ---

// ### ✅ **Modern C++: enum class (Recommended)**

// ```cpp
// enum class State {
//     RUNNING,
//     WAITING,
//     STOPPED
// };

// int main() {
//     State s = State::RUNNING;

//     // if (s == RUNNING) ❌ ERROR
//     if (s == State::RUNNING) {
//         cout << "Thread is running" << endl;
//     }
// }
// ```

// ```cpp
// // BENEFITS OF enum class:
// // 1. Strongly typed
// // 2. No name pollution
// // 3. Safer than traditional enum
// // 4. Preferred in modern C++
// ```

// ---

// ### 🔹 **enum vs enum class (Interview Table in Comments)**

// ```cpp
// // enum:
// // - Weakly typed
// // - Implicit conversion to int allowed
// // - Names leak into scope
// //
// // enum class:
// // - Strongly typed
// // - No implicit int conversion
// // - Scoped (use EnumName::VALUE)
// // - Safer and modern
// ```

// ---

// ### 🔹 **Enum size & storage**

// ```cpp
// // By default enum uses int as underlying type
// // enum class allows specifying size:

// enum class Mode : char {
//     AUTO,
//     MANUAL
// };
// ```

// ---

// ### ⭐ **One-Line Interview Answer**

// ```cpp
// // enum is a user-defined type used to represent a fixed set of named constants,
// // improving readability and safety compared to raw integers.
// ```

// ---

// ### 🚀 **When to use enum (Interview Tip)**

// ```cpp
// // Use enum when:
// // - A variable can have only a limited set of values
// // - You want readable and maintainable code
// // - Representing states, options, or modes
// ```

