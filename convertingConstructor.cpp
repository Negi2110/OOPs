// # ✅ **Converting Constructor – Interview Notes**

// ### ✔ What is a Converting Constructor?

// A **constructor that takes exactly one parameter** (or multiple parameters but only the first one without default) is called a:

// 🟢 **Converting Constructor**
// because it allows **implicit conversion** from the parameter type → to the class type.

// ---

// ### ✔ What does it do?

// It lets C++ automatically convert:

// ```
// int  →  Conversion object
// ```

// without explicitly writing a constructor call.

// ---

// ### ✔ Example of implicit conversion

// ```cpp
// Conversion conv = 25;   // int → Conversion object
// ```

// This calls the constructor:

// ```cpp
// Conversion(int value)
// ```

// This is automatic (implicit conversion).

// ---

// # ✅ **Code with Comments (Interview Ready)**

#include <iostream>
using namespace std;

class Conversion {
private:
    int a;

public:
    // Converting constructor
    // Because it takes ONE parameter (int),
    // it allows implicit conversion from int → Conversion.
    Conversion(int value) : a(value) {
        cout << "Converting constructor called, a = " << a << endl;
    }
};

int main() {

    // Implicit conversion happens here:
    // 25 (int) is automatically converted into a Conversion object.
    Conversion conv = 25;   // SAME as: Conversion conv(25);

    return 0;
}


// # 🧠 **Why does Conversion conv = 25; work?**

// Because `Conversion(int value)` is a **converting constructor**, allowing C++ to interpret:

// ```
// 25 as a Conversion object
// ```

// So:

// ```cpp
// Conversion conv = 25;
// ```

// is equivalent to:

// ```cpp
// Conversion conv(25);
// ```

// ---

// # ⚠️ IMPORTANT Interview Note

// Implicit conversions can sometimes cause **unexpected behavior**.

// To disable implicit conversion and force only explicit construction, add:

// ```cpp
// explicit Conversion(int value);
// ```

// Then this will NOT work:

// ```cpp
// Conversion conv = 25;  // ❌ ERROR after adding explicit
// ```

// But this still works:

// ```cpp
// Conversion conv(25);   // ✔ OK
// ```

// ---

// # 📌 **Copy-Paste Interview Summary**

// * A converting constructor is a **single-argument constructor** that allows implicit type conversion.
// * Enables statements like:

//   ```cpp
//   ClassName obj = value;
//   ```
// * Useful for:

//   * Wrapper classes
//   * Unit conversions
//   * Temporary objects
// * Use `explicit` to prevent accidental implicit conversions.

// ---

// If you want, I can also explain **explicit vs implicit constructors** with examples.
