// # ✅ **Parameters (By Reference) – Interview Notes**

// ### **1. What is happening in this example?**

// * A `Command` object (`cmd`) is created inside `main`.
// * It is passed to the `NPC` object's `Perform` function.
// * The `Perform` function accepts a **reference** to a `Command`:

//   ```cpp
//   void Perform(Command& c)
//   ```
// * This means **no copy** of the object is created.
//   `c` becomes an **alias** for `cmd`.

// ---

// # 🧠 **Why pass by reference?**

// * **Efficient**: avoids copying large objects.
// * **Allows modification**: function can change the original object.
// * **Same memory location** is used by both `cmd` and `c`.

// ---

// # 🚀 **Full Code With Commentary (Interview Quality)**

// ```cpp
#include <iostream>
using namespace std;

class Command {
public:
    int id;

    // Constructor using initializer list
    Command(int id) : id(id) {}

    void Print() {
        cout << id << endl;
    }
};

class NPC {
public:
    // Pass-by-reference: Command& c
    // 'c' is an alias to the actual Command object passed in main.
    // No copy is made. Operates directly on the same object.
    void Perform(Command& c) {
        c.Print();   // Calls Print() on the SAME object passed from main
    }
};

int main() {
    Command cmd(20);   // Create a Command object
    NPC npc;           // Create NPC object
    
    cmd.Print();       // Output: 20
    
    npc.Perform(cmd);  // Pass 'cmd' by reference
                        // Inside Perform(), c refers to the SAME cmd object

    return 0;
}
// ```

// ---

// # 📌 **Key Interview Takeaways**

// ### ✔ 1. Pass-by-reference does **not create a copy**

// `Command& c` refers to the **exact same object** as `cmd`.

// ### ✔ 2. More efficient than pass-by-value

// Especially for classes with many members.

// ### ✔ 3. Allows the function to modify the original object

// Any change to `c` affects `cmd`.

// ### ✔ 4. Syntax uses `&` in parameter list

// ```cpp
// void Perform(Command& c)
// ```

// ### ✔ 5. The main object and the reference share the same memory location

// ---

// If you want, I can give you a **pass by reference vs pass by pointer vs pass by value** comparison — a very common exam/interview question.
