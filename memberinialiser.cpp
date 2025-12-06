#include<iostream>
using namespace std;

class MyClass {
     int x;
public:
int getX() const { return x; }
   MyClass(int val):x(val) {}
};
int main() {
    MyClass obj(5);
    cout<<obj.getX()<<endl;
    return 0;
}