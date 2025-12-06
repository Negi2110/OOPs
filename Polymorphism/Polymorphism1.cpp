#include<iostream>
class Model {
    public:
    void Draw() {
        std::cout<<"Draw model"<<std::endl;
    }
};
class Car : public Model {
    public:
    void Draw() {
        std::cout<<"Draw car"<<std::endl;
    }
};

int main() {
    Model *model = new Model();
    Car *car = new Car();
    Model *poly = new Car();
    model->Draw();
    car->Draw();
    poly->Draw();

    delete model;
    delete car;
    delete poly;
    return 0;
}