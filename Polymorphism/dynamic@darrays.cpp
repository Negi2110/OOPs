
// # ✅ **Dynamic 2D Arrays — Explained**

// A dynamic 2D array in C++ is created using **pointer to pointer** (`type**`).

// This lets you create a matrix where both dimensions can be chosen at **runtime**.

// ---

// # 🟦 Step 1 — Declare a pointer-to-pointer

// ```cpp
// int **myArray;
// ```

// This does NOT create any array yet.
// It just creates a pointer on the stack that will point to the first row.

// ```
// myArray
//    |
//   nullptr
// ```

// ---

// # 🟦 Step 2 — Allocate an array of pointers (rows)

// ```cpp
// myArray = new int*[SIZE];
// ```

// This creates the **first dimension** (rows) on the **heap**:

// ```
// myArray →
//    +----+----+----+----+----+
//    | R0 | R1 | R2 | R3 | ...|
//    +----+----+----+----+----+
//     |    |    |    |
//  nullptr ...
// ```

// Each `myArray[i]` is a pointer that will later point to a row.

// ---

// # 🟦 Step 3 — Allocate each row individually

// ```cpp
// for(int n = 0; n < SIZE; n++)
//     myArray[n] = new int[SIZE];
// ```

// Now each pointer points to a 1D dynamic array:

// ```
// myArray →
//    +----+----+----+----+----+
//    | R0 | R1 | R2 | R3 | ...|
//    +----+----+----+----+----+
//      |    |    |    |
//      v    v    v    v
//    [0 0 0 0 ...]   (row 0)
//    [0 0 0 0 ...]   (row 1)
//    [0 0 0 0 ...]   (row 2)
// ```

// This is a full **dynamic 10x10 matrix**.

// ---

// # 🟦 Step 4 — Access elements like normal 2D array

// ```cpp
// myArray[0][0] = 53;
// ```

// Meaning:

// * Row 0
// * Column 0
// * Set value to 53

// ---

// # ⭐ Full Code (from slide)

// ```cpp
// const int SIZE = 10;
// int **myArray;

// myArray = new int*[SIZE];

// for(int n = 0; n < SIZE; n++)
//     myArray[n] = new int[SIZE];

myArray[0][0] = 53;
// ```

// ---

// # 🚀 Visualization of the Entire Structure

// ```
// Stack:
// myArray
//   |
//   v
// Heap (array of row pointers):
// +------+------+------+------+
// | *R0 | *R1 | *R2 | *R3 | ...
// +------+------+------+------+
//    |      |      |
//    v      v      v
// Heap (rows):
// Row 0 → [int int int int ...]
// Row 1 → [int int int int ...]
// Row 2 → [int int int int ...]
// ```

// You now have a **fully dynamic 2D array**.

// ---

// # 🔥 Summary (Interview Level)

// | Step                      | Meaning                           |
// | ------------------------- | --------------------------------- |
// | `int** arr;`              | Pointer to pointer (for 2D array) |
// | `arr = new int*[rows];`   | Allocates row pointers            |
// | `arr[i] = new int[cols];` | Allocates each row                |
// | `arr[i][j]`               | Access element like normal array  |

// ---

// # Want me to explain **Dynamic 3D arrays** next, or how to **delete** a dynamic 2D array properly?
