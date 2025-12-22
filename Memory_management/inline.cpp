
// In this example, the class `Fast` demonstrates different ways inline functions can be defined in C++. 
//Functions defined **inside the class body** are automatically considered **inline**, even if the `inline` keyword is not explicitly used. 
//Functions declared in the class and defined **outside** can still be inline if the `inline` keyword is used either in the declaration or in the definition. 
//The purpose of inlining is to reduce function call overhead for **small and frequently used functions**, but it is only a suggestion to the compiler and not guaranteed.


#include <iostream>
using namespace std;

/*
 INTERVIEW PERSPECTIVE:
 This class demonstrates inline functions
 defined both inside and outside the class.
*/
class Fast {
private:
    int data;

public:
    /*
     INTERVIEW PERSPECTIVE:
     Constructor defined inside the class.
     Automatically treated as inline.
    */
    Fast() {
        data = 0;
    }

    /*
     INTERVIEW PERSPECTIVE:
     Function defined inside the class.
     Implicitly inline (no keyword needed).
    */
    void SetData(int value) {
        data = value;
    }

    /*
     INTERVIEW PERSPECTIVE:
     Declared inline inside the class,
     defined outside the class.
    */
    inline bool IsEven();

    /*
     INTERVIEW PERSPECTIVE:
     Declared without inline here,
     but definition will include inline.
    */
    void Increment();
};

/*
 INTERVIEW PERSPECTIVE:
 Even though inline keyword is NOT written here,
 the function is still inline because it was
 declared inline inside the class.
*/
bool Fast::IsEven() {
    return (data % 2 == 0);
}

/*
 INTERVIEW PERSPECTIVE:
 inline keyword is written in the definition.
 So this function will be treated as inline
 even though the declaration did not include inline.
*/
inline void Fast::Increment() {
    data++;
}

int main() {
    Fast obj;

    /*
     INTERVIEW PERSPECTIVE:
     Small functions like these are good candidates
     for inlining.
    */
    obj.SetData(10);
    obj.Increment();

    cout << "Is data even? " << obj.IsEven() << endl;

    return 0;
}
// ```

// ---

// ## 🧠 Key Interview Takeaways (Must Mention)

// * Functions defined **inside a class** are implicitly inline
// * `inline` can be used in **declaration or definition**
// * Compiler may **ignore** inlining for complex functions
// * Best suited for **small, frequently called functions**
// * Inlining improves performance by removing call overhead

// ---

// ## ✅ One-Line Interview Answer

// > *“Inline functions reduce function call overhead by expanding the function body at compile time, but the compiler decides whether inlining actually occurs.”*

