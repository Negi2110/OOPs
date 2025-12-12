#include <iostream>
using namespace std;

class Model {
private:
    int id;

public:
    // Parameterized constructor only
    // Because we defined this, the compiler will NOT generate a default constructor.
    //Model(){}-we can also define this to fix the issue
    //Model(int id=0){}-this will also fix the issue
    Model(int modelID) {
        id = modelID;
    }
};

class Car : public Model {
public:
    Car(int carID)
        // ❌ PROBLEM: No default Model() exists.
        // The compiler tries to call Model() before executing Car(),
        // but Model(int) is the ONLY constructor available.
        //
        // To fix: we MUST explicitly call the correct base constructor:
        // Car(int carID) : Model(carID) { }
    {
    }
};

int main() {
    Car *carB = new Car(3);  // ❌ Error: Model() does not exist
    return 0;
}
