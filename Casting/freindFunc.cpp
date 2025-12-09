#include <iostream>
#include <vector>
using namespace std;

/*
====================================================
WEAPON CLASS
====================================================
- Has a PRIVATE member isMounted
- Normally this cannot be accessed outside the class
- We declare a friend function so it CAN access it
*/

class Weapon {
private:
    bool isMounted;   // ✅ PRIVATE data (normally hidden)

public:
    Weapon(bool mounted) : isMounted(mounted) {}

    /*
    --------------------------------------------
    FRIEND FUNCTION DECLARATION
    --------------------------------------------
    - This tells the compiler:
      "This external function is allowed to access
       my private members."
    */

    friend vector<Weapon> getUnMountedWeapons(const vector<Weapon>& weapons);
};


/*
====================================================
FRIEND FUNCTION DEFINITION (OUTSIDE THE CLASS)
====================================================
- This is NOT a member of Weapon
- But it can STILL access:
  ✅ Weapon::isMounted (private)
*/

vector<Weapon> getUnMountedWeapons(const vector<Weapon>& weapons) {

    vector<Weapon> unMounted;

    for (const Weapon& w : weapons) {

        /*
        --------------------------------------------
        ✅ Directly accessing PRIVATE MEMBER
        ✅ This is allowed ONLY because this
           function is declared as FRIEND
        --------------------------------------------
        */

        if (w.isMounted == false) {
            unMounted.push_back(w);
        }
    }

    return unMounted;
}


/*
====================================================
MAIN FUNCTION
====================================================
*/

int main() {

    vector<Weapon> weapons;

    weapons.emplace_back(true);   // Mounted weapon
    weapons.emplace_back(false);  // Unmounted weapon
    weapons.emplace_back(false);  // Unmounted weapon

    /*
    --------------------------------------------
    Call the FRIEND FUNCTION
    --------------------------------------------
    */

    vector<Weapon> result = getUnMountedWeapons(weapons);

    cout << "Number of unmounted weapons = " << result.size() << endl;

    return 0;
}
