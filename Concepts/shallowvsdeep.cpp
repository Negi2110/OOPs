// # Shallow vs Deep Copy in C++

#include <iostream>
#include <utility> // for std::move
using namespace std;

/*
 PART 1: Shallow copy (default copy constructor)
 - data pointer is copied by address -> both objects point to same memory
 - destructor deletes same memory twice -> undefined behaviour / crash
*/
class Shallow {
public:
    int* data;

    Shallow(int value) {
        data = new int(value);
        cout << "Shallow ctor: allocated " << *data << " at " << data << endl;
    }

    // Compiler-provided copy constructor (shallow) will copy the pointer value.
    // ~Shallow() will delete 'data' when object goes out of scope -> double delete.
    ~Shallow() {
        cout << "Shallow dtor: deleting " << (data ? to_string(*data) : string("null"))
             << " at " << data << endl;
        delete data; // Danger: if two objects share same pointer, this causes double-delete.
    }
};

/*
 PART 2: Deep copy (user-defined copy constructor + copy assignment)
 - Allocates new memory and copies value so objects own separate memory
 - Safe to destroy independently
*/
class Deep {
public:
    int* data;

    Deep(int value) {
        data = new int(value);
        cout << "Deep ctor: allocated " << *data << " at " << data << endl;
    }

    // Copy constructor -> deep copy
    Deep(const Deep& other) {
        data = new int(*other.data);
        cout << "Deep copy ctor: copied value " << *data << " to " << data << endl;
    }

    // Copy assignment -> deep copy with self-assignment check
    Deep& operator=(const Deep& other) {
        if (this == &other) return *this;
        delete data;                   // free old
        data = new int(*other.data);   // allocate new copy
        cout << "Deep copy assignment: assigned value " << *data << " to " << data << endl;
        return *this;
    }

    ~Deep() {
        cout << "Deep dtor: deleting " << (data ? to_string(*data) : string("null"))
             << " at " << data << endl;
        delete data;
    }
};

/*
 PART 3: Rule of 5 (Adds move semantics)
 - If your class manages resources, implement:
    - destructor
    - copy ctor
    - copy assignment
    - move ctor
    - move assignment
 - Moves transfer ownership without allocation/copying.
*/
class RuleOfFive {
public:
    int* data;

    // Normal constructor
    RuleOfFive(int value = 0) : data(new int(value)) {
        cout << "ROF ctor: allocated " << *data << " at " << data << endl;
    }

    // Copy constructor (deep copy)
    RuleOfFive(const RuleOfFive& other) : data(new int(*other.data)) {
        cout << "ROF copy ctor: copied " << *data << " to " << data << endl;
    }

    // Copy assignment
    RuleOfFive& operator=(const RuleOfFive& other) {
        if (this == &other) return *this;
        delete data;
        data = new int(*other.data);
        cout << "ROF copy assign: assigned " << *data << " to " << data << endl;
        return *this;
    }

    // Move constructor (steal resources)
    RuleOfFive(RuleOfFive&& other) noexcept : data(other.data) {
        other.data = nullptr;
        cout << "ROF move ctor: moved resource to " << data << endl;
    }

    // Move assignment (steal resources)
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        if (this == &other) return *this;
        delete data;
        data = other.data;
        other.data = nullptr;
        cout << "ROF move assign: moved resource to " << data << endl;
        return *this;
    }

    ~RuleOfFive() {
        cout << "ROF dtor: deleting resource at " << data << endl;
        delete data;
    }
};

int main() {
    cout << "\n--- SHALLOW copy demo (UNSAFE) ---\n";
    {
        Shallow a(10);
        cout << "Creating shallow b = a (uses default shallow copy)\n";
        Shallow b = a; // shallow copy: b.data == a.data
        cout << "a.data = " << a.data << ", *a.data = " << *a.data << endl;
        cout << "b.data = " << b.data << ", *b.data = " << *b.data << endl;
        cout << "Leaving block will call two destructors -> double-delete (UB)\n";
    }
    // NOTE: The program may crash above due to double-delete. If it crashes,
    // skip running SHALLOW section or comment it out.

    cout << "\n--- DEEP copy demo (SAFE) ---\n";
    {
        Deep a(20);
        cout << "Creating deep b = a (invokes deep copy constructor)\n";
        Deep b = a; // deep copy: separate allocations
        cout << "a.data = " << a.data << ", *a.data = " << *a.data << endl;
        cout << "b.data = " << b.data << ", *b.data = " << *b.data << endl;

        cout << "Assign b = a (invokes deep copy assignment)\n";
        b = a;
        cout << "After assignment, b.data = " << b.data << ", *b.data = " << *b.data << endl;
    }

    cout << "\n--- RULE OF 5 (move semantics) demo ---\n";
    {
        RuleOfFive a(30);
        cout << "Copy constructing c from a (deep copy)\n";
        RuleOfFive c = a; // copy ctor

        cout << "Move constructing d from temporary RuleOfFive(40)\n";
        RuleOfFive d = RuleOfFive(40); // move ctor (RVO/move may apply)

        cout << "Move assigning e from std::move(c)\n";
        RuleOfFive e;
        e = std::move(c); // move assign: c.data becomes nullptr

        cout << "After move, c.data = " << c.data << ", e.data = " << e.data << endl;
    }

    cout << "\n--- End of program ---\n";
    return 0;
}
// ```

// ---

// ## Expected behaviour / sample output (explanatory)

// > **Important:** The SHALLOW demo can cause a crash (double-delete). If you run this, you may see program abort during the shallow section. Comment out the shallow section when running tests to avoid a crash.

// A typical run (with the shallow section commented or skipped) might print:

// ```
// --- DEEP copy demo (SAFE) ---
// Deep ctor: allocated 20 at 0x55f8d2f8eeb0
// Creating deep b = a (invokes deep copy constructor)
// Deep copy ctor: copied value 20 to 0x55f8d2f8ef00
// a.data = 0x55f8d2f8eeb0, *a.data = 20
// b.data = 0x55f8d2f8ef00, *b.data = 20
// Assign b = a (invokes deep copy assignment)
// Deep copy assignment: assigned value 20 to 0x55f8d2f8ef00
// After assignment, b.data = 0x55f8d2f8ef00, *b.data = 20
// Deep dtor: deleting 20 at 0x55f8d2f8ef00
// Deep dtor: deleting 20 at 0x55f8d2f8eeb0

// --- RULE OF 5 (move semantics) demo ---
// ROF ctor: allocated 30 at 0x55f8d2f8eeb0
// ROF copy ctor: copied 30 to 0x55f8d2f8ef00
// ROF ctor: allocated 40 at 0x55f8d2f8ef50
// ROF move ctor: moved resource to 0x55f8d2f8ef50
// ROF ctor: allocated 0 at 0x55f8d2f8efb0
// ROF move assign: moved resource to 0x55f8d2f8ef00
// After move, c.data = 0, e.data = 0x55f8d2f8ef00
// ROF dtor: deleting resource at 0x55f8d2f8ef00
// ROF dtor: deleting resource at 0x55f8d2f8ef50
// ROF dtor: deleting resource at 0x55f8d2f8efb0
// ```

// ---

// ## Interview-friendly summary you can paste

// * **Shallow copy**: default copy constructor copies member-wise (addresses for pointers). If class owns dynamic memory, shallow copy causes multiple objects to own same resource → double delete / UB.
// * **Deep copy**: implement copy constructor (and copy assignment) to allocate new memory and copy content. Safe and appropriate for classes owning resources. This is part of the **Rule of 3**: if you need a destructor, you likely need copy ctor and copy assignment.
// * **Rule of 5** (C++11+): if your class manages resources, implement destructor, copy ctor, copy assignment, **move ctor**, and **move assignment** to support efficient moves and safe ownership transfer.
// * Always prefer RAII and smart pointers (`std::unique_ptr`, `std::shared_ptr`) to manage resources and avoid writing these manually when possible.

// ---

// If you want I can:

// * Provide a **version using `unique_ptr`** that demonstrates the safer modern C++ approach.
// * Remove the unsafe shallow demo and add unit-test style checks.
// * Convert this into a one-page PDF with explanations for interviews. Which would you like?
