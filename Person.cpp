#include "Person.h"

Person::Person()
{
    cout << "Person created." << endl;
}
void Person::Crawl()
{
    cout << "Person is crawling." << endl;
}
void Person::Run()
{
    cout << "Person is running." << endl;
}
void Person::Stand()        
{
    cout << "Person is standing." << endl;
}
void Person::Walk()
{
    cout << "Person is walking." << endl;
}
Person::~Person()
{
    cout << "Person destroyed." << endl;
}