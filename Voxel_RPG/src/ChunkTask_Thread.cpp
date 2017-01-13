#pragma once
#include "ChunkTask_Thread.h"
#include "ChunkTask_ThreadPool.h"
#include "ChunkTask.h"

namespace ChunkTasks {

	ChunkTask_Thread::ChunkTask_Thread(ChunkTasks::ChunkTask_ThreadPool* pool) {
		m_ownerPool = pool;
		m_ownerPool->m_threadCount.fetch_add(1);
		m_thread = new std::thread(&ChunkTasks::ChunkTask_Thread::threadMain, this);
	}

	ChunkTask_Thread::~ChunkTask_Thread() {
		if (m_thread->joinable()) {
			m_thread->join();
		}
		m_ownerPool->m_threadCount.fetch_sub(1);
		delete m_thread;
	}

	void ChunkTask_Thread::threadMain() {
		ChunkTask* task = nullptr;
		while (m_ownerPool->isActive()) {
			{
				std::unique_lock<std::mutex> lck(m_ownerPool->m_mutex);
				if (m_ownerPool->isActive() && m_ownerPool->m_taskQueue.empty()) {
					m_ownerPool->m_conditionVariable.wait(lck);
				}

				if (m_ownerPool->isActive()) {
					m_ownerPool->_getTask(task);
				}
			}

			if (task != nullptr) {
				m_ownerPool->m_workingThreads.fetch_add(1);
				task->executeTask();
			}

			m_ownerPool->m_workingThreads.fetch_sub(1);
			task = nullptr;
		}
	}

}