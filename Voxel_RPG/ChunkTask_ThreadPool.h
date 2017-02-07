#pragma once
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>
#include <chrono>
#include <iostream>

namespace ChunkTasks {

	class ChunkTask;

	class ChunkTask_ThreadPool {

	public:
		static const int DEFAULT_THREAD_COUNT = 2;

		ChunkTask_ThreadPool();
		ChunkTask_ThreadPool(int startingThreadCount);
		~ChunkTask_ThreadPool();

		int getThreadCount() { return m_threadCount; }
		int getWorkingThreads() { return m_workingThreads; }
		bool isActive() { return m_active.load(); };
		bool isPaused() { return m_paused; };
		void pause() { m_paused = true; };
		void resume() { m_paused = false; };

		void init();
		void addTask(ChunkTasks::ChunkTask*);

	private:
		friend class ChunkTask_Thread;

		std::vector<ChunkTasks::ChunkTask_Thread*> m_workers;

		bool m_paused;
		std::atomic<bool> m_active;
		std::atomic<int> m_threadCount;
		std::atomic<int> m_workingThreads;

		std::mutex m_mutex;
		std::condition_variable m_conditionVariable;
		std::queue<ChunkTasks::ChunkTask*> m_taskQueue;

		void _getTask(ChunkTasks::ChunkTask*);


	};
}