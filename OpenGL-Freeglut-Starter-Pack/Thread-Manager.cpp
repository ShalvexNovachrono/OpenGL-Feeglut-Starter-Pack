#include "Thread-Manager.h"

CThreadManager::CThreadManager(size_t threadCount) {
    for (size_t i = 0; i < threadCount; ++i)
        workers.Append(thread(&CThreadManager::WorkerLoop, this));
}

CThreadManager::~CThreadManager() {
    stopping = true;
    condition.notify_all();
    for (auto& t : workers)
        if (t.joinable()) t.join();
}

future<void> CThreadManager::Enqueue(function<void()> job) {
    auto task = make_shared<packaged_task<void()>>(move(job));
    future<void> future = task->get_future();
    {
        lock_guard<mutex> lock(queueMutex);
        taskQueue.push([task] { (*task)(); });
        activeTasks++;
    }
    condition.notify_one();
    return future;
}

void CThreadManager::WaitAll() {
    unique_lock<mutex> lock(doneMutex);
    doneCondition.wait(lock, [this] {
        return activeTasks.load() == 0;
    });
}

void CThreadManager::WorkerLoop() {
    while (true) {
        function<void()> job;
        {
            unique_lock<mutex> lock(queueMutex);
            condition.wait(lock, [this] {
                return !taskQueue.empty() || stopping.load();
            });

            if (stopping && taskQueue.empty())
                return;

            job = move(taskQueue.front());
            taskQueue.pop();
        }

        job(); 

        if (--activeTasks == 0)
            doneCondition.notify_all();
    }
}