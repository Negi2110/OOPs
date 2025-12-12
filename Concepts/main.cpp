#include <iostream>
#include "Person.h"
using namespace std;

int main()
{
    Person *p=  new Person();
    p->Crawl();
    p->Walk();
    p->Stand();
    p->Run();
    delete p;   
    return 0;
}