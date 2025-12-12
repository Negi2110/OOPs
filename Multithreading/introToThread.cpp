// TOPIC: Introduction to Threads in C++ (C++11)

// QUESTION:
// 1. What do you understand by a thread? Give one example in C++.

// ANSWER:
// A thread is the smallest unit of execution within a process. Every C++ application starts with a
// default thread—the main() function—and additional threads can be created to perform tasks in parallel.
// Threads help achieve concurrency and can significantly improve performance, especially when tasks are
// independent or involve waiting (e.g., I/O operations).
//
// Real-world examples of multithreading:
//   (a) Web browsers use multiple threads—each tab or network request may run on a separate thread.
//   (b) MS Word uses threads for spell-checking, formatting, and autosaving simultaneously.
//   (c) Visual Studio Code uses threads for IntelliSense, background analysis, and UI responsiveness.
// SUMMARY:
// Threads allow a program to run multiple tasks concurrently.
// C++11 introduced std::thread for portable, modern multithreading.
// You can create threads using:
//   1. Function Pointer
//   2. Lambda Function
//   3. Functor (Function Object)
//   4. Member Function
//   5. Static Member Function
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;
ull OddSum = 0, EvenSum = 0;

void findEven(ull start, ull end)
{
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 0) EvenSum += i;
}
void findOdd(ull start, ull end)
{
    for (ull i = start; i <= end; ++i)
        if ((i & 1) != 0) OddSum += i;
}

int main()
{
    ull start = 0, end_value = 1900000000ULL;   // renamed 'end' -> 'end_value'

    auto start_time = high_resolution_clock::now();   // renamed
    std:thread t1(findEven, start, end_value);
    std::thread t2(findOdd, start, end_value);
    // findEven(start, end_value);
    // findOdd(start, end_value);
    t1.join();
    t2.join();
    auto end_time = high_resolution_clock::now();     // renamed

    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Even Sum: " << EvenSum << endl;
    cout << "Odd Sum: " << OddSum << endl;
    cout << "Time taken: " << duration.count() / 1000 << " s" << endl;
    return 0;
}
// #include <iostream>
// #include <thread>
// #include <chrono>
// #include <algorithm>
// using namespace std;
// using namespace std::chrono;
// typedef long long int  ull;

// void findEven(ull start, ull end, ull* EvenSum) {
// 	for (ull i = start; i <= end; ++i){
// 		if (!(i & 1)){
// 			*(EvenSum) += i;
// 		}
// 	}
// }

// void findOdd(ull start, ull end, ull* OddSum) {
// 	for (ull i = start; i <= end; ++i){
// 		if (i & 1){
// 			(*OddSum) += i;
// 		}
// 	}
// }

// int main() {
	
// 	ull start = 0, end = 1900000000;

// 	ull OddSum = 0;
// 	ull EvenSum = 0;
    
//     auto startTime = high_resolution_clock::now(); 

// 	// // WITH THREAD
//     std::thread t1(findEven, start, end, &(EvenSum));
//     std::thread t2(findOdd, start, end, &(OddSum));

// 	t1.join();
// 	t2.join();

// 	// // WITHOUT THREAD
// 	// findEven(start,end, &EvenSum);
// 	// findOdd(start, end, &OddSum);
//     auto stopTime = high_resolution_clock::now(); 
//     auto duration = duration_cast<microseconds>(stopTime - startTime);

// 	cout << "OddSum : " << OddSum << endl;
// 	cout << "EvenSum : " << EvenSum << endl;

// 	cout << "Sec: " << duration.count()/1000000 << endl;

// 	return 0;
// }

// “In C++, we include <chrono> whenever we need to work with time in a precise and type-safe way. The <chrono> library provides clocks such as high_resolution_clock, steady_clock, and system_clock to capture timestamps. 
// It also provides strongly typed duration units like seconds, milliseconds, and microseconds, which prevents mixing up time units. When we measure execution time, we typically take two time_points from a clock—before and after an operation—and subtract them to get a duration. 
// Since durations don’t implicitly convert, we use duration_cast to convert them into the unit we want, such as milliseconds. Overall, <chrono> is the modern and reliable way to do timing, benchmarking, and time calculations in C++.”
/*
================================================================================
⚡ WHY THE PROGRAM BECAME 6× FASTER AFTER USING:
    g++ introToThread.cpp -O3 -pthread -std=c++17 -o struct
================================================================================

1️⃣  Without optimization:
        g++ introToThread.cpp -o struct

    - This produces a DEBUG-like binary:
        • No loop optimizations
        • No inlining
        • No vectorization (SIMD)
        • No loop unrolling
        • Slow % modulo operations
        • Slow global memory writes
        • Threads still run, but overhead > benefit
    - Result: My program took ~6 seconds.

--------------------------------------------------------------------------------

2️⃣  With optimization:
        g++ introToThread.cpp -O3 -pthread -std=c++17 -o struct

    This turns ON the **Release mode** optimizations.
    Here's what each flag does:

    ------------------------------------------------------------------------
    🔹 -O3  (FULL OPTIMIZATION)
    ------------------------------------------------------------------------
    - The compiler transforms slow loops into highly optimized machine code.
    - Major effects:
        ✓ Replaces expensive modulo (i % 2) with bit check (i & 1)
        ✓ Loop unrolling → processes multiple iterations per loop
        ✓ Vectorization (SIMD, AVX2/AVX512) → processes many integers at once
        ✓ Moves global writes outside the loop → reduces cache traffic
        ✓ Better branch prediction or branch removal
    - Turns a simple loop into something 4×–10× faster.

    ------------------------------------------------------------------------
    🔹 -pthread  (ENABLE REAL MULTITHREADING)
    ------------------------------------------------------------------------
    - Ensures proper thread creation on Linux.
    - Links pthread library internally.
    - Allows threads to run truly concurrently across CPU cores.
    - Without this, threads may not be scheduled efficiently.

    ------------------------------------------------------------------------
    🔹 -std=c++17  (MODERN LANGUAGE + OPTIMIZATION ENABLED)
    ------------------------------------------------------------------------
    - Enables modern C++ features.
    - Allows compiler to use newer optimization rules.
    - Ensures correct behavior of std::thread, std::chrono, etc.

--------------------------------------------------------------------------------

3️⃣ Combined effect:
    -O3 gives faster *per-thread* performance.
    -pthread allows threads to run on separate CPU cores (16 in my case!)
    -std=c++17 ensures clean, optimized modern C++ code.

    Result:
        BEFORE optimization → 6 seconds
        AFTER  optimization → 1 second
    ✔ Almost **6× faster**
    ✔ Without changing a single line of code

--------------------------------------------------------------------------------

4️⃣ Why multithreading was SLOW before optimization:
    - Debug/no-opt builds are too slow → thread overhead > benefit
    - Expensive modulo operations
    - Global variables cause cache ping-pong in slow builds
    - Two threads doing 2× work in parallel = wastes CPU cycles

    After enabling -O3:
    - CPU vectorizes the loop
    - Threads run in parallel
    - Each core does optimized work
    - No unnecessary global memory updates

--------------------------------------------------------------------------------

🏁 FINAL SUMMARY
--------------------------------------------------------------------------------
Using:
    g++ introToThread.cpp -O3 -pthread -std=c++17 -o struct

makes the program dramatically faster because:

    ✔ Loop is auto-optimized and vectorized (SIMD)
    ✔ Global writes minimized
    ✔ Branches removed or simplified
    ✔ Work split across CPU cores
    ✔ Compiler generates Release-mode machine code

This is why all real-world C++ applications are built in **Release mode**, not Debug mode.
================================================================================
*/
// | Operating System            | Compile command                               |
// | --------------------------- | --------------------------------------------- |
// | **Linux (g++)**             | `g++ file.cpp -O3 -pthread -std=c++17 -o app` |
// | **Windows (MinGW g++)**     | `g++ file.cpp -O3 -std=c++17 -o app.exe`      |
// | **Windows (MSVC - cl.exe)** | `cl /O2 /std:c++17 file.cpp`                  |
