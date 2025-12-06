#include <iostream>
using namespace std;
struct myStruct
{  
   int x;
    int y;
    int z;
    int sum() { return x + y + z; }
};
int main() {
    myStruct *obj= new myStruct();
    obj->x = 10;
    obj->y = 20;
    obj->z = 40;
    cout<<"Sum: " << obj->sum() << endl;
    delete obj;
    return 0;
}   
