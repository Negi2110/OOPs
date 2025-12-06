#include <iostream>
using namespace std;

inline int add(int a, int b) {
    return a + b;
}
int main() {
    int result = add(5, 10);
    cout << "The sum is: " << result << endl;
    return 0;
}