#include<iostream>
using namespace std;
int main() {
    int *ptr = new int[5];
    cout<<ptr<<endl;
    delete[] ptr;
    return 0;
}