
#include <iostream>
using namespace std;

/*
====================================================
CLASS TEMPLATE DECLARATION
====================================================
- T is a GENERIC TYPE (int, float, double, etc.)
- This is ONLY the declaration of the class
- The constructor is declared but NOT defined here
*/

template <class T>
class Vector2D {
private:
    // ✅ Array of 2 elements of generic type T
    T coordinate[2];

public:
    // ✅ Constructor DECLARATION (definition is outside)
    Vector2D(T x, T y);

    // ✅ Inline member function (defined inside class)
    void Display() {
        cout << "x: " << coordinate[0]
             << " y: " << coordinate[1] << endl;
    }
};


/*
====================================================
CONSTRUCTOR DEFINITION OUTSIDE THE CLASS
====================================================
IMPORTANT TEMPLATE RULES APPLIED HERE:
1. We MUST repeat: template <class T>
2. We MUST use: Vector2D<T>:: before constructor name
3. Constructor has NO return type
*/

template <class T>
Vector2D<T>::Vector2D(T x, T y) {
    coordinate[0] = x;   // ✅ Assign x-coordinate
    coordinate[1] = y;   // ✅ Assign y-coordinate
}


/*
====================================================
MAIN FUNCTION
====================================================
*/

int main() {

    /*
    ====================================================
    TEMPLATE CLASS INSTANTIATION
    ====================================================
    - Here we specify:
        T = int
    - Compiler generates this class internally:

      class Vector2D<int> {
          int coordinate[2];
          ...
      };
    */

    Vector2D<int> v(3, 4);   // ✅ Calls Vector2D<int>::Vector2D(3,4)

    // ✅ Calls inline Display() function
    v.Display();             // Output: x: 3 y: 4

    return 0;
}
// ```

// ---

// ## ✅ What This Example Teaches (Directly from Your Slide)

// * ✅ When a **class template member function is defined outside**, we must:

//   ```cpp
//   template <class T>
//   ClassName<T>::FunctionName(...)
//   ```
// * ✅ The `<T>` after `Vector2D` **connects the function to the template class**
// * ✅ Even if the function does **not explicitly use `T`**, it still **must include `<T>`**
// * ✅ Constructors:

//   * ✅ Still need `Vector2D<T>::`
//   * ✅ Do **NOT** have a return type
// * ✅ Functions defined **inside the class are inline**
// * ✅ Functions defined **outside the class are NOT inline**

// ---

// ## ❌ Very Common Mistakes (Interview Traps)

// ```cpp
// Vector2D::Vector2D(T x, T y) { }   // ❌ WRONG (missing <T>)
// template<class T>
// Vector2D::Vector2D(T x, T y) { }   // ❌ WRONG (missing <T> after class name)
// ```

// ✅ Correct version:

// ```cpp
// template<class T>
// Vector2D<T>::Vector2D(T x, T y) { }
// ```

// ---

// ## 🔥 One-Line Interview Finisher

// > “When defining a class template’s member function outside the class, we must repeat `template<class T>` and use `ClassName<T>::FunctionName`, even for constructors.”

// ---

