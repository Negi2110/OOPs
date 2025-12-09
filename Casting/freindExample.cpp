#include <iostream>
#include <string>
using namespace std;

/*
====================================================
WEAPON CLASS
====================================================
- This class has:
  ✅ One PRIVATE data member: isMounted
  ✅ One PUBLIC data member: name
- Since isMounted is PRIVATE, it CANNOT be accessed
  directly outside this class.
- So we declare a FRIEND function to allow access.
*/

class Weapon {
private:
    bool isMounted;   // ✅ PRIVATE → normally hidden from outside

public:
    string name;      // ✅ PUBLIC → accessible anywhere

    /*
    --------------------------------------------
    PARAMETERIZED CONSTRUCTOR
    --------------------------------------------
    - Initializes name and isMounted
    - This is the only normal way to set isMounted
    */

    Weapon(string desc, bool mounted)
        : name(desc), isMounted(mounted) {}

    /*
    --------------------------------------------
    FRIEND FUNCTION DECLARATION
    --------------------------------------------
    - This is NOT a class member function
    - But it is given SPECIAL ACCESS to:
      ✅ private member isMounted
    - It returns an array of Weapon pointers
    */

    friend Weapon** UnmountedWeapons(Weapon**, int*);
};


/*
====================================================
FRIEND FUNCTION DEFINITION
====================================================
- This function:
  ✅ Is NOT part of the Weapon class
  ✅ Still accesses Weapon::isMounted (PRIVATE!)
  ✅ That is only possible because it was declared FRIEND
*/

Weapon** UnmountedWeapons(Weapon** weaponList, int* size) {

    /*
    --------------------------------------------
    Allocate a new array of Weapon pointers
    --------------------------------------------
    - Same size as the original list
    - This will store ONLY unmounted weapons
    */

    Weapon** unMounted = new Weapon*[*size];

    int i = 0;   // index for unMounted array

    /*
    --------------------------------------------
    Loop through all weapons
    --------------------------------------------
    */

    for (int n = 0; n < *size; n++) {

        /*
        --------------------------------------------
        ✅ ACCESSING PRIVATE MEMBER isMounted
        --------------------------------------------
        - This is normally NOT allowed
        - But it works because this function is FRIEND
        */

        if (!weaponList[n]->isMounted) {     // ✅ private access allowed
            unMounted[i] = weaponList[n];    // store unmounted weapon
            i++;
        }
    }

    /*
    --------------------------------------------
    Update the size to NEW count
    --------------------------------------------
    */

    *size = i;

    /*
    --------------------------------------------
    Return the new list of unmounted weapons
    --------------------------------------------
    */

    return unMounted;
}


/*
====================================================
MAIN FUNCTION (TESTING)
====================================================
*/

int main() {

    /*
    --------------------------------------------
    Creating an array of Weapon pointers
    --------------------------------------------
    */

    int size = 4;

    Weapon** weapons = new Weapon*[size];

    weapons[0] = new Weapon("Gun", true);    // ✅ Mounted
    weapons[1] = new Weapon("Missile", false); // ✅ Unmounted
    weapons[2] = new Weapon("Rocket", false);  // ✅ Unmounted
    weapons[3] = new Weapon("Cannon", true);   // ✅ Mounted

    /*
    --------------------------------------------
    Call the FRIEND FUNCTION
    --------------------------------------------
    */

    Weapon** unMountedList = UnmountedWeapons(weapons, &size);

    /*
    --------------------------------------------
    Print Unmounted Weapons
    --------------------------------------------
    */

    cout << "Unmounted Weapons:\n";

    for (int i = 0; i < size; i++) {
        cout << unMountedList[i]->name << endl;
    }

    return 0;
}


// ✅ What This Code Proves (Interview Gold Points)

// ✅ isMounted is PRIVATE

// ✅ It is accessed inside UnmountedWeapons()

// ✅ This is possible ONLY because:

// friend Weapon** UnmountedWeapons(Weapon**, int*);


// ✅ The friend function:

// ❌ Is NOT inside the class

// ✅ Still has full access to private data

// ✅ This is a controlled break of encapsulation

// ✅ Why Friend Is Needed Here

// Without friend, this line would cause a COMPILER ERROR:

// if (!weaponList[n]->isMounted)  // ❌ PRIVATE → illegal without friend

// 🔥 One-Line Interview Finisher

// “This example shows how a friend function can access a class’s private member to filter unmounted weapons, even though it is not a class member.”