#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>
#include <chrono>
#include <iostream>
//#include "WorkerThread.h"
class WorkerThread;
class Task {
public:
	bool isComplete() { return  m_complete.load(); };
	virtual void executeTask() = 0;
protected:
	std::atomic<bool> m_complete;
};

class TimedPrint : public Task {
public:

	int m_time;

	TimedPrint(int time, std::string) {
		m_time = time;
	}

	virtual void executeTask() { // called in thread
		std::this_thread::sleep_for(std::chrono::seconds(m_time));
		std::cout << "This thread slept for " << m_time << " seconds!!";
		m_complete.store(true);
	}
};


class ChunkThreadPool {
	
public:
	static const int DEFAULT_THREAD_COUNT = 2;

	ChunkThreadPool();
	ChunkThreadPool(int startingThreadCount);
	~ChunkThreadPool();

	int getThreadCount() { return m_threadCount; }
	int getWorkingThreads() { return m_workingThreads; }
	bool isActive() { return m_active; };
	bool isPaused() { return m_paused; };
	void pause() { m_paused = true; };
	void resume() { m_paused = false; };

	void init();
	void addTask(Task*);

private:
	friend class WorkerThread;
	std::vector<WorkerThread*> m_workers;
	
	bool m_paused;
	std::atomic<bool> m_active;
	std::atomic<int> m_threadCount;
	std::atomic<int> m_workingThreads;
	
	std::mutex m_mutex;
	std::condition_variable m_conditionVariable;
	std::queue<Task*> m_taskQueue;

	void _getTask(Task* task);
	
	
};

//Constructor and deconstructor
ChunkThreadPool::ChunkThreadPool() {
	m_threadCount = ChunkThreadPool::DEFAULT_THREAD_COUNT;

}

ChunkThreadPool::ChunkThreadPool(int startingThreadCount) {
	m_threadCount = startingThreadCount;
}

ChunkThreadPool::~ChunkThreadPool() {
	if (m_active) {
		m_active = false;
		for (int i = 0; i < m_workers.size(); i++) {
			delete m_workers[i];
		}
	}
}
//Public
void ChunkThreadPool::init() {
	if (!m_active.load()) {
		m_active.store(true);
		for (int i = 0; i < m_workers.size(); i++) {
			m_workers.push_back(new WorkerThread(this));
		}
	}
}

void ChunkThreadPool::addTask(Task* task) {
	{
		std::lock_guard<std::mutex> lck(m_mutex);
		m_taskQueue.push(task);
	}
	m_conditionVariable.notify_one();
	
}
//Private

void ChunkThreadPool::_getTask(Task* task) {
	std::lock_guard<std::mutex> lck(m_mutex);
	task = m_taskQueue.front();
	if (!m_taskQueue.empty()) {
		m_taskQueue.pop();
	}
}