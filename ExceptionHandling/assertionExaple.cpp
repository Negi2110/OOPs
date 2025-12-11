

// This class `Game` uses **assertions to validate input parameters** during development:

// ### ✔ In the constructor:

// ```cpp
// assert(maxPlayers > 1);
// ```

// This ensures a valid number of players.
// If someone tries to create a game with only **1 player**, the assertion **fails**, and the program terminates.

// ### ✔ In `GetPlayer(int index)`:

// ```cpp
// assert(index >= 0 && index < maxPlayers);
// ```

// This ensures the index is **within valid array bounds**.

// If `index` is invalid (like 2, while max players = 1), the assertion fails → **array out-of-bounds access prevented**.

// ### ❌ The main() in the slide:

// ```cpp
// Game *myGame = new Game(1);    // INVALID – maxPlayers == 1
// Player *opponent = myGame->GetPlayer(2);  // OUT OF BOUNDS
// ```

// Both assertions **fail**.

#include <iostream>
#include <cassert>   // For assert()
using namespace std;

class Player {};     // Dummy Player class for this example

class Game {
private:
    int maxPlayers;   // Maximum number of players allowed
    Player** players; // Dynamic array of Player pointers

public:
    // Constructor
    Game(int maxPlayers) : maxPlayers(maxPlayers) {

        /*
            Assert ensures maxPlayers > 1.
            If someone passes 1 or 0:
            - Assertion fails
            - Program stops
            - Prevents creating an invalid game
        */
        assert(maxPlayers > 1);

        // Allocate memory for given number of players
        players = new Player*[maxPlayers];

        // Initialize pointers to nullptr for safety
        for (int i = 0; i < maxPlayers; i++)
            players[i] = nullptr;
    }

    // Function to get a player by index
    Player* GetPlayer(int index) {

        /*
            Assert checks:
                - index >= 0
                - index < maxPlayers
            Prevents out-of-bounds access.
        */
        assert(index >= 0 && index < maxPlayers);

        return players[index];
    }
};

int main() {

    // ❌ This will fail the constructor assertion because maxPlayers is 1
    Game* myGame = new Game(1);

    // ❌ This will also fail because index 2 is out of bounds
    Player* opponent = myGame->GetPlayer(2);

    return 0;
}
// ```

// ---

// # 💥 **What Happens When You Run This Program (Debug Mode)**

// ### 1️⃣ First failure

// ```
// assert(maxPlayers > 1)
// ```

// Because maxPlayers = 1
// → Program TERMINATES immediately
// → Error message:

// ```
// Assertion failed: maxPlayers > 1, file main.cpp, line XX
// ```

// ### 2️⃣ Second failure (if NDEBUG is defined)

// If assertion is disabled and constructor passes, then:

// ```
// assert(index >= 0 && index < maxPlayers)
// ```

// fails at `GetPlayer(2)`.

// ---

// # 🎯 **What This Example Teaches**

// * Assertions help catch **logic errors early in development**.
// * Assertions prevent:

//   * invalid game configurations
//   * array out-of-bound indexing
// * Assertions **do NOT run in release builds** (if NDEBUG is defined).
// * Assertions are **not** for handling user input—they are for developers.

// ---

// # 📝 **One-Line Interview Answer**

// > “Assertions enforce conditions that must always be true during development, and they immediately stop the program when violated, helping catch bugs early.”

// ---
// In this assertions example, the constructor uses `assert(maxPlayers > 1)` to ensure the game always starts with at least two players, and the `GetPlayer()` function uses `assert(index >= 0 && index < maxPlayers)` to verify that array access is within valid bounds before returning a player pointer. 
// In the given code, the game is incorrectly created with only one player and later the program tries to access player index 2, so both assertions are logically incorrect; however, only the **first** assertion fails because assertions terminate the program immediately when a condition evaluates to false.
//  As a result, the program stops at `assert(maxPlayers > 1)`, prints an error message showing the failed expression, file name, and line number, and execution is aborted. Assertions are designed for debugging and catching programming mistakes early, and they validate assumptions that must always be true but are not meant for handling user input or runtime errors.


// C++ provides a built-in exception handling mechanism similar to other object-oriented languages, enabling developers to detect errors and handle them separately from the main program logic. 
// This separation improves code clarity by keeping normal execution flow distinct from error-handling code, and it also helps prevent crashes caused by unexpected runtime failures. 
// By allowing structured error reporting and controlled recovery, exceptions play a crucial role in building robust, reliable, and maintainable software solutions.