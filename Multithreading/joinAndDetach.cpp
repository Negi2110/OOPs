// TOPIC: Use of join(), detach() and joinable() in Threads in C++ (C++11)

//
// JOIN NOTES:
// 0. Once a thread is started we wait for this thread to finish by calling join() on the thread object.
// 1. Calling join() twice will result in program termination.
// 2. If needed we should check whether the thread is joinable before calling join() using joinable().
//

//
// DETACH NOTES:
// 0. detach() is used to separate the newly created thread from the parent thread.
// 1. Always check if the thread is joinable before detaching, otherwise we may end up calling detach() twice,
//    which results in program termination.
// 2. If we detach a thread and main() returns early, then the detached thread continues running in the background.
//    (Detached thread execution is independent of main).
//

//
// NOTES:
// 0. Either join() or detach() MUST be called on every std::thread object.
//    Otherwise, when the thread object is destroyed, the destructor checks if the thread is still joinable().
//    If yes, it will terminate the program.
//    (Reason: C++ does not allow a joinable thread object to go out of scope).
//

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void run(int count)
{
    while (count-- > 0)
    {
        cout << "Aman NEGI" << endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
int main()
{
    thread t1(run, 5);
    cout << "Main thread is waiting for t1 to finish execution" << endl;
    // Always check if the thread is joinable before calling join()

    t1.join();
    if (t1.joinable())
        t1.join(); // Program will terminate here because we are calling join() twice on the same thread object. 'std::system_error'what():  Invalid argument
    cout << "t1 joined successfully" << endl;
    return 0;
}

// WHAT IS joinable() ?
//
// joinable() is a member function of std::thread that checks whether a thread 
// still represents an active, running, or joinable thread of execution.
//
// In simple terms: joinable() tells us whether we can safely call join() or detach() 
// on a thread object.
//
// WHAT DOES joinable() CHECK ?
//
// 1. It returns true if the std::thread object actually owns a running thread.
// 2. It returns false in these cases:
//      (a) The thread has not been started (default-constructed thread).
//      (b) The thread has already been joined.
//      (c) The thread has already been detached.
//      (d) The thread object was moved-from.
//
// WHY IS joinable() IMPORTANT (INTERVIEW POINTS)?
//
// • To avoid calling join() twice. (Second join → program terminates)
// • To avoid calling detach() twice. (Second detach → program terminates)
// • To prevent std::terminate from being called when a joinable thread object 
//   goes out of scope (destructor checks joinable()).
// • It is a safety check to ensure proper thread lifecycle management.
//
// INTERVIEW SUMMARY:
//   joinable() is used to check whether a thread is in a valid state where 
//   join() or detach() can be safely called. It prevents program termination 
//   caused by incorrect thread handling.
