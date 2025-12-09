
#include <iostream>
using namespace std;

/*
====================================================
CLASS DEFINITION
====================================================
- MyClass has a NON-STATIC member function Add()
- Because it is NON-STATIC:
  ✅ It belongs to an OBJECT
  ✅ It requires a `this` pointer to execute
*/

class MyClass {
public:
    // ✅ Normal NON-STATIC member function
    int Add(int a, int b) {
        return a + b;
    }
};

int main() {

    /*
    ====================================================
    1️⃣ CREATE AN OBJECT OF THE CLASS
    ====================================================
    - Since Add() is NOT static, it must be called
      using an object of MyClass.
    */

    MyClass obj;


    /*
    ====================================================
    2️⃣ DECLARE A POINTER TO A MEMBER FUNCTION
    ====================================================
    SYNTAX:
        returnType (ClassName::*pointerName)(parameterTypes);

    Here:
        int          → return type
        MyClass::*   → says this is a MEMBER FUNCTION of MyClass
        ptr          → pointer name
        (int, int)   → parameter list of Add()
    */

    int (MyClass::*ptr)(int, int);


    /*
    ====================================================
    3️⃣ ASSIGN THE MEMBER FUNCTION ADDRESS TO THE POINTER
    ====================================================
    - We MUST use:
        &ClassName::FunctionName
    - Because this is NOT a normal function
    */

    ptr = &MyClass::Add;   // ✅ Stores address of MyClass::Add


    /*
    ====================================================
    4️⃣ CALL THE MEMBER FUNCTION USING THE POINTER
    ====================================================
    - Since ptr is a MEMBER FUNCTION pointer:
      ✅ We CANNOT call it like a normal pointer → ptr(3,9) ❌
      ✅ We MUST bind it with an object using `.*`

    Correct syntax:
        (object .* pointer)(arguments)
    */

    int answer = (obj.*ptr)(3, 9);   // ✅ Calls obj.Add(3,9)


    /*
    ====================================================
    5️⃣ PRINT THE RESULT
    ====================================================
    */

    cout << answer << endl;   // Output: 12

    return 0;
}
// ```

// ---

// ## ✅ What This Program Demonstrates (Interview Gold Points)

// * ✅ Difference between **normal function pointer** and **member-function pointer**
// * ✅ Why we must write:

//   ```
//   int (MyClass::*ptr)(int,int);
//   ```
// * ✅ Why we **must use `&MyClass::Add`**
// * ✅ Why we **must call it using `(obj.*ptr)(args)`**
// * ✅ How **non-static member functions require an object**

// ---

// ## 🔥 One-Line Interview Finisher

// > “This program demonstrates how a pointer to a non-static member function is declared, assigned using `&ClassName::FunctionName`, and invoked through an object using the `.*` operator.”

