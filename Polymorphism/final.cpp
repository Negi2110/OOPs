// Perfect — this slide is about the **`final` keyword in C++11**, which is the **opposite partner of `override`**. I’ll explain it in the **same simple, interview-focused way** you liked before.

// ---

// # ✅ What is `final` in C++? (Simple Meaning)

// `final` is used to **STOP further overriding or inheritance**.

// It can be used in **two ways**:

// 1. ✅ On a **virtual function** → Stops overriding
// 2. ✅ On a **class** → Stops inheritance

// ---

// # ✅ 1. `final` on a Virtual Function (Stops Overriding)

// ### 🔹 Base Class

// ```cpp
class GameObject {
public:
    virtual void Register() final {   // ✅ final used here
        cout << "Register GameObject\n";
    }
};
// ```

// ### 🔹 Derived Class

// ```cpp
class Car : public GameObject {
public:
    void Register() override {   // ❌ COMPILER ERROR
        cout << "Car Register\n";
    }
};

// ### ✅ Why Error Happens

// * `Register()` is marked `final` in base
// * That means: **“No derived class is allowed to override this.”**
// * Compiler stops it at **compile time**

// ---

// ### ✅ One-Line Meaning (Function Level)

// > “`final` on a virtual function prevents any further overriding in derived classes.”

// ---

// # ✅ 2. `final` on a Class (Stops Inheritance)

// // ```cpp
class Immutable final {   // ✅ final on class
private:
    int readOnlyData;

public:
    Immutable(int data) : readOnlyData(data) {}
    int GetData() { return readOnlyData; }
};
```

// Now if someone tries:

// ```cpp
class Test : public Immutable { };   // ❌ COMPILER ERROR
```

// ❌ Error because:

// * `Immutable` is marked `final`
// * So **no class can inherit from it**

// ---

// ### ✅ One-Line Meaning (Class Level)

// > “`final` on a class makes that class non-inheritable.”

// ---

// # ✅ Why `final` is Used (Real Reasons)

// * ✅ To **protect important logic** from being changed
// * ✅ To **lock behavior in large projects**
// * ✅ To **avoid incorrect overriding**
// * ✅ To **help compiler optimizations** (can remove vtable calls)
// * ✅ To **increase safety in frameworks & engines**

// ---

// # ✅ Difference Between `override` and `final` (Quick Interview Table)

// | Keyword          | Purpose                     |
// | ---------------- | --------------------------- |
// | `override`       | Forces correct overriding   |
// | `final`          | Prevents further overriding |
// | `final` on class | Prevents inheritance        |

// ---

// # 🔥 Final One-Line Interview Answer

// > “`final` prevents further overriding of a virtual function, and when applied to a class, it makes the class non-inheritable.”



// ---

// ### ✅ Final Interview-Perfect Meaning

// > **`virtual` is used to enable and extend runtime polymorphism, while `final` is used to restrict or stop it.**

// ---

// ### ✅ What each keyword really does

// * ✅ **`virtual`**

//   * Allows a function to be **overridden**
//   * Enables **runtime polymorphism**
//   * Uses **vtable + vptr**

// * ✅ **`final`**

//   * **Stops further overriding** of a virtual function
//   * Or **stops inheritance** when applied to a class
//   * Can **remove runtime dispatch** and improve performance

// ---

// ### 🔥 One-Line Interview Finisher

// > “`virtual` enables runtime polymorphism, while `final` restricts or completely locks it.”

// ---

// You now understand the **full control system of runtime polymorphism**:

// * `virtual` → opens the door
// * `override` → checks correctness
// * `final` → locks the door ✅
