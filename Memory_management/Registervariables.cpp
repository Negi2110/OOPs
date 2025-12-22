// ## 📌 Register Variables — Interview Perspective (Theory)

// A **register variable** is a local variable declared using the `register` keyword to **suggest** to the compiler that the variable should be stored in a CPU register instead of RAM. Since registers are faster than memory, this can *potentially* improve performance, especially in loops or frequently accessed variables. However, the `register` keyword is only a **recommendation**, not a command—the compiler may ignore it. Register variables can only be **local variables or function parameters**, not global or static variables. In modern C++ compilers, aggressive optimization often makes the `register` keyword unnecessary, as the compiler automatically decides the best storage location.

// ---

// ## 🧠 Key Interview Points (Side Notes)

// * `register` improves **access speed**, not logic
// * It is only a **hint** to the compiler
// * Can be used only for **local variables or parameters**
// * **Address (`&`) cannot be taken** for register variables
// * Modern compilers often **ignore `register`**
// * Deprecated in **C++17**


#include <iostream>
using namespace std;

int main() {

    /*
     INTERVIEW PERSPECTIVE:
     'register' suggests storing variable n in a CPU register
     for faster access inside the loop.
    */
    for (register int n = 0; n < 100000000; n++) {

        /*
         INTERVIEW PERSPECTIVE:
         The loop variable is accessed repeatedly,
         making it a potential candidate for register storage.
        */
    }

    /*
     SIDE NOTE (IMPORTANT):
     There may be no visible performance gain because
     modern compilers automatically optimize this.
    */

    return 0;
}


// ## ❌ Invalid Uses (Interview Trap Questions)

// ```cpp
// register int x = 10;
// int* ptr = &x;   // ❌ ERROR: cannot take address of register variable
// ```

// ```cpp
// register int g;  // ❌ ERROR: global variables cannot be register
// ```

// ---

// ## ⚠️ Modern C++ Reality (Must Mention)

// > In modern C++, the `register` keyword is deprecated (C++17) because compilers are better at optimization than programmers.

// ---

// ## ✅ One-Line Interview Answer (Very Important)

// > *“A register variable is a local variable declared with the `register` keyword to suggest faster access by storing it in a CPU register, though modern compilers usually ignore this hint.”*

// ---

// ## 🎯 Strong Interview Closing Line

// > *“Today, performance optimization is best left to the compiler, making `register` largely obsolete.”*

