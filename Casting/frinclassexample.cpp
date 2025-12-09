// Perfect — this slide is showing a **Friend Class version of your earlier Weapon example**, where the logic is moved into a **`WeaponsManager` class instead of a free function**. I’ll now give you a **clean, fully commented engine-style C++ program** that exactly matches what this slide is explaining ✅

// ---

// ## ✅ **Friend Class – Fully Commented Example (WeaponsManager Pattern)**

// ```cpp
// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;

/*
====================================================
WEAPON CLASS
====================================================
- This class holds weapon data.
- The member isMounted is PRIVATE.
- Normally, no other class can access it.
- We declare WeaponsManager as a FRIEND class.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class WeaponsManager;   // ✅ Forward declaration

class Weapon {
private:
    bool isMounted;   // ✅ PRIVATE → hidden from all other classes

public:
    string name;

    // ✅ Constructor to initialize both name and isMounted
    Weapon(string desc, bool mounted)
        : name(desc), isMounted(mounted) {}

    /*
    --------------------------------------------
    FRIEND CLASS DECLARATION
    --------------------------------------------
    - This gives FULL private access of Weapon
      to ALL member functions of WeaponsManager
    */

    friend class WeaponsManager;
};


/*
====================================================
WEAPONS MANAGER CLASS (FRIEND CLASS)
====================================================
- This class now CONTAINS the earlier logic
  (instead of a standalone friend function).
- Since this class is declared as FRIEND inside Weapon,
  it can directly access Weapon::isMounted (PRIVATE).
*/

class WeaponsManager {
public:

    /*
    --------------------------------------------
    MEMBER FUNCTION TO GET UNMOUNTED WEAPONS
    --------------------------------------------
    - This function replaces the old friend function.
    - It directly accesses private member isMounted
      because WeaponsManager is a FRIEND class.
    */

    vector<Weapon*> getUnMountedWeapons(vector<Weapon*>& weaponList) {

        vector<Weapon*> unMounted;

        for (Weapon* w : weaponList) {

            // ✅ Direct access to PRIVATE member (because of friend class)
            if (!w->isMounted) {
                unMounted.push_back(w);
            }
        }

        return unMounted;
    }
};


/*
====================================================
MAIN FUNCTION (TESTING)
====================================================
*/

int main() {

    vector<Weapon*> weapons;

    weapons.push_back(new Weapon("Gun", true));       // ✅ Mounted
    weapons.push_back(new Weapon("Missile", false));  // ✅ Unmounted
    weapons.push_back(new Weapon("Rocket", false));   // ✅ Unmounted
    weapons.push_back(new Weapon("Cannon", true));    // ✅ Mounted

    WeaponsManager manager;

    // ✅ Manager extracts all unmounted weapons using private data
    vector<Weapon*> result = manager.getUnMountedWeapons(weapons);

    cout << "Unmounted Weapons:\n";
    for (Weapon* w : result) {
        cout << w->name << endl;
    }

    return 0;
}
// ```

// ---

// ## ✅ **What This Example Proves (Exactly What Your Slide Says)**

// * ✅ `isMounted` is **PRIVATE** in `Weapon`
// * ✅ `WeaponsManager` needs access to that private member
// * ✅ So `WeaponsManager` is declared as:

// ```cpp
// friend class WeaponsManager;
// ```

// * ✅ Now **ALL member functions of `WeaponsManager`** can access:

//   * `Weapon::isMounted`
//   * `Weapon::name`
// * ✅ This is the **Manager–Entity pattern in practice**

// ---

// ## ✅ **Why This is Better Than a Friend Function in Engines**

// | Friend Function          | Friend Class (Manager)     |
// | ------------------------ | -------------------------- |
// | One function gets access | Whole manager gets access  |
// | Not object-oriented      | Proper engine architecture |
// | Hard to extend           | Easy to extend             |
// | No internal state        | Manager can maintain state |

// ---

// ## 🔥 **One-Line Interview Finisher**

// > “In this example, `WeaponsManager` is made a friend of `Weapon` so it can directly access the private member `isMounted` and manage weapon filtering efficiently in a manager–entity architecture.”

// ---

