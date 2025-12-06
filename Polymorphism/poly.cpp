#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/*
  This file demonstrates:
  - static (compile-time) binding vs dynamic (runtime) binding
  - virtual functions and the vtable concept (explained in comments)
  - pure virtual functions (abstract classes / interfaces)
  - virtual destructors and why they are necessary
  - overriding vs hiding (and use of 'override' keyword)
  - object slicing (when storing derived by-value into base)
  - arrays/containers of base-class pointers holding different derived types
  - covariant return type example
  - calling base-class implementation explicitly
  - final specifier
  - small notes on cost & vtable layout
*/

/*------------------------
  Base class (non-virtual)
  ------------------------
  This class shows static binding: methods are invoked based on the static type.
*/
class NonVirtualBase {
public:
    void greet() { cout << "NonVirtualBase::greet (static binding)\n"; }
};

/*------------------------
  Base class with virtuals
  ------------------------
  This is the proper polymorphic base:
  - virtual functions enable dynamic dispatch (runtime choice of override)
  - classes with at least one virtual will typically have a vptr pointing to a vtable
*/
class Animal {
public:
    // Virtual function: enabling runtime polymorphism
    virtual void speak() {
        cout << "Animal::speak (base)\n";
    }

    // Pure virtual (makes the class abstract) - uncomment to see abstract use:
    // virtual void pure() = 0;

    // Virtual destructor: VERY important when deleting derived via base pointer.
    // If destructor is not virtual, deleting through base* leads to undefined behavior.
    virtual ~Animal() {
        cout << "Animal destructor\n";
    }
};

/* Derived overrides speak() */
class Dog : public Animal {
public:
    void speak() override {               // override: compiler checks we are actually overriding
        cout << "Dog::speak (woof)\n";
    }

    ~Dog() override {                     // override optional for destructor
        cout << "Dog destructor\n";
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Cat::speak (meow)\n";
    }

    ~Cat() override {
        cout << "Cat destructor\n";
    }
};

/*------------------------
  Object slicing demo
  ------------------------
  When you store a derived object by-value into a base object,
  any derived-specific parts are 'sliced' off. This eliminates polymorphism.
*/
class Shape {
public:
    virtual void draw() { cout << "Shape::draw\n"; }
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() override { cout << "Circle::draw\n"; }
    void radiusSpecific() { cout << "circle-only method\n"; }
};

/*------------------------
  Covariant return types demo
  ------------------------
  A virtual function may return a pointer/reference to a derived type (covariant)
*/
class Fruit {
public:
    virtual Fruit* clone() { return new Fruit(*this); }
    virtual ~Fruit() {}
};

class Apple : public Fruit {
public:
    Apple* clone() override { return new Apple(*this); } // covariant return: Apple* replaces Fruit*
};

/*------------------------
  Final and calling base implementation
  ------------------------
  - final prevents further overrides.
  - base::method() calls base implementation explicitly.
*/
class Vehicle {
public:
    virtual void start() { cout << "Vehicle::start\n"; }
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    void start() override final {                // final prevents subclasses from overriding start()
        cout << "Car::start (calls base and then its own behaviour)\n";
        Vehicle::start();                        // explicit call to base implementation
    }
};

// Uncommenting below will cause compile error because start() is final in Car.
// class SportsCar : public Car {
// public:
//     void start() override { } // error: cannot override final function
// };

/*------------------------
  Demonstration helpers
  ------------------------*/

void static_vs_dynamic_binding_demo() {
    cout << "=== static_vs_dynamic_binding_demo ===\n";

    NonVirtualBase nv;
    nv.greet();               // calls NonVirtualBase::greet

    NonVirtualBase* nvptr = new NonVirtualBase();
    nvptr->greet();           // still calls NonVirtualBase::greet (static binding)

    // If we had DerivedHidden with same method name but not virtual,
    // calling via base pointer still calls base's method (static binding).

    delete nvptr;
    cout << '\n';
}

void virtual_function_demo() {
    cout << "=== virtual_function_demo (dynamic binding) ===\n";

    Animal* a1 = new Animal();
    Animal* a2 = new Dog();
    Animal* a3 = new Cat();

    // All calls use Animal* type, but dynamic binding calls derived overrides:
    a1->speak();   // Animal::speak
    a2->speak();   // Dog::speak  (runtime chosen)
    a3->speak();   // Cat::speak

    // Deleting via base pointer -> triggers virtual destructors in derived
    delete a1;     // Animal destructor
    delete a2;     // Dog destructor -> Animal destructor
    delete a3;     // Cat destructor -> Animal destructor

    cout << '\n';
}

void slicing_demo() {
    cout << "=== slicing_demo ===\n";

    Circle c;
    Shape s = c;  // object slicing: derived part is sliced off, s is a pure Shape
    s.draw();     // calls Shape::draw, not Circle::draw because s is a Shape object (not pointer/ref)

    // Preserve polymorphism by using pointer or reference:
    Shape* sp = new Circle();
    sp->draw();   // Circle::draw (dynamic dispatch)
    delete sp;

    cout << '\n';
}

void array_of_base_pointers_demo() {
    cout << "=== array_of_base_pointers_demo ===\n";
    // container of base pointers holding different derived types (polymorphic container)
    vector<unique_ptr<Animal>> zoo;
    zoo.emplace_back(make_unique<Dog>());
    zoo.emplace_back(make_unique<Cat>());

    for (auto &a : zoo) {
        a->speak(); // calls appropriate override for each element
    }

    // unique_ptr cleans up automatically; virtual destructor ensures proper deletion order
    cout << '\n';
}

void covariant_return_demo() {
    cout << "=== covariant_return_demo ===\n";

    Fruit* f = new Fruit();
    Fruit* f_clone = f->clone();     // returns Fruit*
    delete f_clone;
    delete f;

    Apple* ap = new Apple();
    Fruit* ap_clone_as_fruit = ap->clone(); // returns Apple* but convertible to Fruit*
    delete ap_clone_as_fruit;
    delete ap;

    cout << '\n';
}

void final_and_base_call_demo() {
    cout << "=== final_and_base_call_demo ===\n";

    Vehicle* v = new Car();
    v->start();   // Car::start (declared final), which also calls Vehicle::start internally
    delete v;

    cout << '\n';
}

/*------------------------
  Main: run all demos
  ------------------------*/
int main() {
    // 1) static vs dynamic binding
    static_vs_dynamic_binding_demo();

    // 2) virtual functions and virtual destructor behavior
    virtual_function_demo();

    // 3) object slicing vs pointer/reference polymorphism
    slicing_demo();

    // 4) container / array of base pointers (polymorphic collection)
    array_of_base_pointers_demo();

    // 5) covariant return example
    covariant_return_demo();

    // 6) final + calling base implementation
    final_and_base_call_demo();

    // Quick summary print
    cout << "=== Summary (interview notes) ===\n";
    cout << "- 'virtual' enables runtime polymorphism (dynamic dispatch via vtable).\n";
    cout << "- Always make base destructor virtual if you intend to delete via base pointer.\n";
    cout << "- Use 'override' to let compiler check your overrides — catches bugs.\n";
    cout << "- Object slicing happens when storing derived by-value into base; prefer pointers/references.\n";
    cout << "- 'final' stops further overriding; covariant returns allow derived pointer/refs as return types.\n";
    cout << "- vtable adds a small runtime cost (indirection) but is essential for polymorphism.\n";

    return 0;
}
