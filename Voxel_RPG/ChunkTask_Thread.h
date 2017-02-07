#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>
#include "ChunkTask_ThreadPool.h"

namespace ChunkTasks {

	class ChunkTask_Thread {
	public:
		ChunkTask_Thread(ChunkTasks::ChunkTask_ThreadPool* pool);
		~ChunkTask_Thread();
		void threadMain();
	private:
		ChunkTasks::ChunkTask_ThreadPool* m_ownerPool;
		std::thread* m_thread;
	};
}