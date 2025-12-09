// ## ✅ What is the **Manager–Entity Pattern**?

// > The **Manager–Entity pattern** is a design where:

// * **Entity** = represents a game object or simulation object (Player, Enemy, Weapon, Vehicle, etc.)
// * **Manager** = controls the **lifecycle and internal state** of many entities (create, delete, update, activate, deactivate)

// So:

// * **Entity holds data**
// * **Manager controls behavior & ownership**

// ---

// ## ✅ Why `friend` Is Used Here

// In engines, we often want:

// * ✅ Entities to keep their data **private**
// * ✅ But managers to still **modify internal state directly**
// * ✅ Without exposing setters everywhere

// That’s exactly where **friend class** is used.

// ---

// ## ✅ Real Engine-Style Example (Simple & Accurate)


#include <iostream>
using namespace std;

class EntityManager;   // Forward declaration

class Entity {
private:
    int id;            // Internal ID (not public!)
    bool isAlive;      // Internal lifecycle flag

public:
    Entity(int id) : id(id), isAlive(true) {}

    void draw() {
        cout << "Drawing entity " << id << endl;
    }

    // ✅ EntityManager is made FRIEND
    friend class EntityManager;
};

class EntityManager {
public:
    void destroy(Entity& e) {
        // ✅ Direct access to PRIVATE member of Entity
        e.isAlive = false;
        cout << "Entity destroyed by manager\n";
    }
};

int main() {
    Entity player(101);
    EntityManager manager;

    player.draw();            // ✅ Normal behavior
    manager.destroy(player); // ✅ Manager directly changes private state
}
// ```

// ---

// ## ✅ What This Achieves (Why Engines Use It)

// * ✅ **Entity stays encapsulated** for the rest of the program
// * ✅ **Only the Manager gets low-level control**
// * ✅ No unnecessary:

//   * getters
//   * setters
//   * public flags
// * ✅ **High performance** (no overhead)
// * ✅ **Strong ownership model** (manager truly controls entity life)

// ---

// ## ✅ Where You See This in Real Systems

// * 🎮 Game Engines → `Entity` + `EntityManager`
// * 🧠 AI Systems → `Agent` + `AgentManager`
// * 🚗 Simulations → `Vehicle` + `VehicleController`
// * 🎥 Rendering → `RenderObject` + `RenderManager`

// ---

// ## 🔥 One-Line Interview Definition

// > “In the Manager–Entity pattern, the manager controls the lifecycle and internal state of entities, and `friend` is often used so the manager can safely access private entity data without exposing it publicly.”

// ---

