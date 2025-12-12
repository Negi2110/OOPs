#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void run(int count)
{
    while (count-- > 0)
    {
        cout <<count<< "Aman NEGI" << endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
int main()
{
    thread t1(run, 5);
    cout << "Main thread is waiting for t1 to finish execution" << endl;
    t1.detach();
    //double detach will cause program termination
    if(t1.joinable())
       t1.detach(); // Program will terminate here because we are calling detach() twice on the same thread object. 'std::system_error'what():  Invalid argument
    cout << "t1 detached successfully" << endl;
    return 0;
}
// Detached thread = independent execution, not tied to parent thread object.
// But it still belongs to the same process.
// When main() returns, process ends -> ALL threads stop immediately.
// So detached threads do NOT outlive the process.

// ABOUT detach() — INTERVIEW PERSPECTIVE:
//
// detach() is used to separate (detach) the child thread from the parent thread.
// After detaching:
//    • The parent thread (main thread) no longer controls the child thread.
//    • The child thread runs independently in the background.
//    • This is often called a "daemon" or "background" thread.
//
// WHAT detach() DOES INTERNALLY:
//
// 1. It breaks the association between the std::thread object and the actual OS thread.
// 2. The OS thread continues running on its own.
// 3. The std::thread object no longer represents a running thread (joinable() becomes false).
//
// PARENT–CHILD RELATION AFTER DETACH:
//
// • Before detach(): 
//       - Parent is responsible for joining/detaching the child.
//       - Child’s lifetime is tied to parent’s thread object.
//
// • After detach():
//       - Child thread becomes independent (no parent control).
//       - Parent thread continues without waiting for the child.
//       - The child may continue running even after main() returns 
//         (if the OS keeps it alive).
//
// THREAD EXECUTION SUSPENSION POINT:
//
// • A detached thread cannot be "joined" again or "suspended" by the parent.
// • It runs until its function completes naturally.
// • If main() ends before the detached thread finishes, the program may terminate 
//   the child thread early (depends on OS / runtime).
//
// WHY detach() IS DANGEROUS (HIGH-VALUE INTERVIEW POINT):
//
// • You lose control — no way to know if the task finished.
// • If the detached thread accesses destroyed resources → undefined behavior.
// • Should be used for fire-and-forget background tasks only.
//
// COMMON INTERVIEW QUESTIONS:
//
// Q1: Should you ALWAYS detach a thread?  
// A: No. Use it only when you deliberately want background execution.
//
// Q2: What happens if you call detach() twice?  
// A: Program terminates (thread no longer joinable).
//
// Q3: Must I call join() or detach()?  
// A: YES. If a joinable thread is destroyed, std::terminate() is called.
//
// SUMMARY: 
// detach() creates a background thread that runs independently while the main 
// thread continues execution without waiting. It must be used carefully as the 
// parent thread loses all control and responsibility over the child thread.
//
