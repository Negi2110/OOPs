// =============================================================
// std::try_lock() in C++11 Multithreading
// =============================================================
//
// 1. std::try_lock() attempts to lock ALL the lockable objects
//    passed to it, one by one, in the given order.
//
//    Syntax:
//      std::try_lock(m1, m2, m3, ..., mn);
//
//    Each argument must be a lockable object
//    (e.g., std::mutex, std::timed_mutex, etc.)
//
// -------------------------------------------------------------
// RETURN VALUE
// -------------------------------------------------------------
//
// 2. If std::try_lock() SUCCESSFULLY locks ALL mutexes:
//      - It returns -1
//
// 3. If std::try_lock() FAILS to lock any mutex:
//      - It returns the ZERO-BASED INDEX of the mutex
//        that could NOT be locked.
//
//    Example:
//      std::try_lock(m1, m2, m3)
//      return value = 1  -> means m2 could not be locked
//
// -------------------------------------------------------------
// FAILURE BEHAVIOR (VERY IMPORTANT)
// -------------------------------------------------------------
//
// 4. If std::try_lock() fails to lock any mutex:
//      - It automatically UNLOCKS all mutexes
//        that it successfully locked earlier.
//
//    This guarantees:
//      - No partial locking
//      - No deadlock
//      - Exception safety
//
// -------------------------------------------------------------
// EXCEPTION SAFETY
// -------------------------------------------------------------
//
// 5. If an exception occurs during std::try_lock():
//      - unlock() is called on all mutexes
//        that were successfully locked
//      - The exception is then rethrown
//
//    This provides STRONG exception safety.
//
// -------------------------------------------------------------
// INTERVIEW NOTES
// -------------------------------------------------------------
//
// • std::try_lock() is NON-BLOCKING.
// • It does NOT wait for any mutex.
// • It attempts each mutex ONCE.
// • Useful when multiple mutexes must be acquired
//   without risking deadlock.
//
// -------------------------------------------------------------
// INTERVIEW ONE-LINER
// -------------------------------------------------------------
//
// std::try_lock() attempts to lock multiple mutexes without blocking;
// it either locks all of them or none, ensuring deadlock-free behavior.
// =============================================================
