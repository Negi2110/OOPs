// # ✅ **What is a Union in C++? (Simple + Interview Definition)**

// A **union** in C++ is a special user-defined data type that allows **multiple variables to share the same memory location**.
// Only **one member can hold a value at a time**, because all members overlap in the same memory block.

// ### 🔥 **Interview Answer (One Line)**

// > “A union is like a struct where all members share the same memory, meaning it uses memory equal to the largest member, and only one member can store a valid value at a time.”

// ---

// # ✅ **Why do we use Unions? (Interview Points)**

// * **Memory optimization** → Most important reason.
// * Useful in **embedded systems**, **hardware drivers**, **network packet interpretation**, where memory is limited.
// * Used for **type punning** → interpret the same bytes in different ways (careful with strict aliasing).
// * Used in **variant data types** where only one member is active.

// ---

// # ✅ **Memory Behavior (Very Important for interviews)**

// If your union is:

// ```cpp
// union Data {
//     int x;      // 4 bytes
//     char c;     // 1 byte
//     double d;   // 8 bytes
// };
// ```

// 👉 The size of the union = **size of the largest member = 8 bytes**
// All members start at the **same memory address**.


#include <iostream>
using namespace std;

union Data {
    int i;
    float f;
    char c;
};

int main() {
    Data d;

    d.i = 10;
    cout << "i = " << d.i << endl;

    d.f = 3.14f;
    cout << "f = " << d.f << endl;

    d.c = 'A';
    cout << "c = " << d.c << endl;

    // Now d.i and d.f are overwritten because same memory is reused
    return 0;
}
// ```

// ### Output:

// Only the **last written value is valid**.

// ---

// # ✅ **Example 2 – Realistic Interview Example (Network/Embedded)**

// ```cpp
#include <iostream>
using namespace std;

union Packet {
    int intValue;
    float floatValue;
    char bytes[4];
};

int main() {
    Packet p;
    p.intValue = 1025;

    cout << "Integer: " << p.intValue << endl;

    cout << "Bytes: ";
    for(int i = 0; i < 4; i++)
        cout << (int)p.bytes[i] << " ";

    return 0;
}
// ```

// ### Why this is asked?

// * Shows how unions help interpret the **same 4 bytes** in different ways
// * Useful in **serialization, embedded systems, endian checking**

// ---

// # ✅ **Example 3 – Union with Struct (Common in Device Drivers)**

// ```cpp
union SensorReading {
    int rawValue;
    struct {
        unsigned low : 8;
        unsigned high : 8;
    } bytes;
};

int main() {
    SensorReading r;
    r.rawValue = 0x1234;

    cout << "Low byte: " << r.bytes.low << endl;
    cout << "High byte: " << r.bytes.high << endl;
}
// ```

// This is used heavily in **microcontrollers** → splitting sensor data into bytes.

// ---

// # 🔥 **Union vs Struct (Interview Table)**

// ```
// +----------------------+-------------------------------+
// | Struct               | Union                         |
// +----------------------+-------------------------------+
// | All members exist    | Only ONE member valid at a    |
// | simultaneously       | time                          |
// +----------------------+-------------------------------+
// | Size = sum of all    | Size = size of largest member |
// | members              |                               |
// +----------------------+-------------------------------+
// | Separate memory for  | Shared memory for all         |
// | each member          | members                       |
// +----------------------+-------------------------------+
// | No overwriting       | Writing one overwrites others |
// +----------------------+-------------------------------+
// ```

// ---

// # 📝 **When NOT to use unions**

// * When you need *all members active at the same time*
// * When you need type safety → use `std::variant` in modern C++
// * When overlapping memory can cause undefined behavior

// ---

// # ⚡ **Modern C++ Alternative (Important)**

// C++17 provides **`std::variant`**, a type-safe union.

// ---


// # ✅ **What is `std::variant`? (Interview Definition)**

// `std::variant` is a **type-safe union** introduced in **C++17** that can hold one value out of several possible types, but **ensures type-safety**, keeps track of which type is active, and prevents undefined behavior that occurs with raw unions.

// ### ⭐ Interview One-liner

// > “`std::variant` is a modern, type-safe replacement for unions that stores one value from a fixed set of types and tracks which type is currently held.”

// ---

// # ✅ **Why `std::variant` Exists? (Key Interview Points)**

// * **Prevents accidental overwriting**, unlike unions
// * **Tracks active type** → avoids bugs
// * **Throws exceptions when accessed incorrectly**
// * Works with **`std::visit`** for pattern-matching-style handling
// * Safer and easier than unions for variant data

// ---

// # ✅ Example 1 — Basic Usage

// ```cpp
#include <variant>
#include <iostream>
using namespace std;

int main() {
    variant<int, float, string> v;

    v = 10;
    cout << get<int>(v) << endl;     // OK

    v = 3.14f;
    cout << get<float>(v) << endl;

    v = string("Hello");
    cout << get<string>(v) << endl;
}
// ```

// `std::variant` automatically destroys the previous value and constructs the new one.

// ---

// # ❌ What happens if you get the wrong type?

// ```cpp
// variant<int, float> v = 10;
// cout << get<float>(v);  // ❌ std::bad_variant_access exception
// ```

// This is *safer than unions*, where wrong access causes undefined behavior.

// ---

// # ✅ Example 2 — Using `std::visit` (Important Interview Topic)

// ```cpp
variant<int, float, string> v = 3.14f;

visit([](auto&& value) {
        cout << "Value = " << value << endl;
    }, v);
// ```

// `std::visit` acts like **pattern matching**, calling the correct lambda based on the active type.

// ---

// # ✅ Example 3 — Checking Current Type

// ```cpp
// variant<int, float, string> v = 10;

// if (holds_alternative<int>(v)) {
//     cout << "v holds int!" << endl;
// }
// ```

// ---

// # 📝 Memory Behavior (Compared with union)

// ```
// Union:      All members share EXACT same memory (dangerous!)
// Variant:    Stores one active type + a type index (safe)
// ```

// `std::variant` uses aligned storage internally and maintains type information.

// ---

// # 🔥 Union vs Variant (Interview Table)

// ```
// +-------------------+-----------------------------+
// |     Union         |        std::variant         |
// +-------------------+-----------------------------+
// | Unsafe            | Type-safe                   |
// | No type tracking  | Stores active type index    |
// | Manual control    | Automatic resource mgmt      |
// | Can cause UB      | Throws exceptions instead   |
// | No destructor mgmt| Calls destructor correctly  |
// +-------------------+-----------------------------+
// // ```

// ---

// # 🎯 When to Use `std::variant`

// Use it when:

// ✔ You need a variable that can hold **one of several types**
// ✔ You want **safety and readability**
// ✔ You want to avoid **raw unions**
// ✔ You want pattern-matching-like behavior

// ---

// # 🎯 When NOT to Use

// Avoid it when:

// ✘ You need low-level memory reinterpretation
// ✘ Performance-critical embedded systems
// ✘ You need overlapping memory like in device drivers → use unions

// ---

// # ⭐ Example: Variant used for Game Events (Common interview example)

// ```cpp
struct Move    { int x, y; };
struct Shoot   { int power; };
struct Jump    { float height; };

using Event = variant<Move, Shoot, Jump>;

void handleEvent(const Event& e) {
    visit([](auto& ev){
        cout << "Handling event: " << typeid(ev).name() << endl;
    }, e);
}

int main() {
    Event e = Shoot{50};
    handleEvent(e);
}

