
#include <iostream>
using namespace std;

/*
====================================================
CLASS TEMPLATE: Vector2D
====================================================
- T is a GENERIC TYPE
- This class can store 2D coordinates of ANY type:
  ✅ int
  ✅ float
  ✅ double
  ✅ etc.
*/

template <class T>
class Vector2D {
private:
    // ✅ Array of 2 elements of generic type T
    // If T = int  → this becomes int coordinate[2]
    // If T = float → this becomes float coordinate[2]
    T coordinate[2];

public:
    /*
    ============================================
    CONSTRUCTOR
    ============================================
    - Takes two values of type T
    - Stores them as x and y
    */
    Vector2D(T x, T y) {
        coordinate[0] = x;   // ✅ x-coordinate
        coordinate[1] = y;   // ✅ y-coordinate
    }

    /*
    ============================================
    DISPLAY FUNCTION
    ============================================
    - Prints both coordinates
    */
    void Display() {
        cout << "x: " << coordinate[0]
             << " y: " << coordinate[1] << endl;
    }
};

int main() {

    /*
    ====================================================
    TEMPLATE CLASS INSTANTIATION
    ====================================================
    - Here we explicitly specify:
        T = int
    - So the compiler generates this class internally:

      class Vector2D<int> {
          int coordinate[2];
          ...
      };
    */

    Vector2D<int> v(3, 4);   // ✅ x = 3, y = 4

    // ✅ Calls Display() for Vector2D<int>
    v.Display();             // Output: x: 3 y: 4

    return 0;
}
// ```

// ---

// ## ✅ What This Example Proves (Interview Gold)

// * ✅ `template<class T>` makes the class **generic**
// * ✅ `T coordinate[2]` adapts to the chosen type
// * ✅ `Vector2D<int>` creates a **real class with int storage**
// * ✅ The compiler generates **separate classes for each type**
// * ✅ This is **compile-time polymorphism**, not runtime

// ---

// ## ✅ If You Did This Instead…

// ```cpp
// Vector2D<float> v(3.5f, 4.2f);
// ```

// Then internally it becomes:

// ```cpp
// class Vector2D<float> {
//     float coordinate[2];
// };
// ```

// ---

// ## 🔥 One-Line Interview Finisher

// > “This example shows a class template where the data type of the 2D vector is decided at object creation time, allowing the same class to work with `int`, `float`, or any numeric type with zero runtime overhead.”

// ---

