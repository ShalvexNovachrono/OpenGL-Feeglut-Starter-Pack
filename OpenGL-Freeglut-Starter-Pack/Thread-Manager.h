#ifndef ThreadManager
#define ThreadManager

#include "Array.h"
#include "main.h"

//https://github.com/harshabose/thread_manager/blob/main/thead_manager.h

class CThreadManager {
    queue<function<void()>> threadQueue;
public:
    /// <summary>
    /// Constructs a CThreadManager object.
    /// </summary>
    /// <param name="threadCount">The number of threads to create in the thread pool. Defaults to the number of hardware concurrency.</param>
    explicit CThreadManager(size_t threadCount = thread::hardware_concurrency());

    /// <summary>
    /// Destroys the CThreadManager object, waiting for all active tasks to complete.
    /// </summary>
    ~CThreadManager();

    /// <summary>
    /// Enqueues a task to be executed by a thread in the pool.
    /// </summary>
    /// <param name="task">The function to be executed.</param>
    future<void> Enqueue(function<void()> task);
    
    /// <summary>
    /// Waits for all currently enqueued tasks to complete.
    /// </summary>
    void WaitAll();
    
    // Delete copy constructor and assignment operator to prevent copying
    CThreadManager(const CThreadManager&) = delete;
    CThreadManager& operator=(const CThreadManager&) = delete;
private:
    /// <summary>
    /// The main loop for each worker thread. Continuously dequeues and executes tasks.
    /// </summary>
    void WorkerLoop();
    
    CArray<thread> workers;
    queue<function<void()>> taskQueue;
    mutex queueMutex;
    condition_variable condition;
    atomic<bool> stopping{ false };
    atomic<int> activeTasks { 0 };
    condition_variable doneCondition;
    mutex doneMutex;
};

#endif
