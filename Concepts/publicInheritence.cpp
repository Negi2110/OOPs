#include <iostream>
using namespace std;

class Model
{
public:
    void Draw()
    {
        std::cout << "Drawing Model" << std::endl;
    }
};
class Car : public Model
{
public:
    void Draw()
    {
        std::cout << "Drawing Car" << std::endl;
    }
    void ChangeGear()
    {
        std::cout << "Changing Car Gear" << std::endl;
    }
};

int main()
{
    Model model;
    Car car;
    model.Draw();
    car.Draw(); // Calls Car's overridden Draw(), not Model's
    car.ChangeGear();
    return 0;
}

// “Car publicly inherits from Model, so it gets all public members.
// If the derived class defines a function with the same name and signature, it overrides the base class version.
// In this example, Car::Draw() overrides Model::Draw(), so calling car.Draw() runs the Car version, not the Model version.”

// Here Car publicly inherits from Model, so it automatically gets all public methods of Model.
// That’s why car.Draw() works even though we did not write a Draw function inside Car.

// Public inheritance models an ‘is-a’ relationship: a Car is a Model.
// Car can extend functionality by adding new functions like ChangeGear().