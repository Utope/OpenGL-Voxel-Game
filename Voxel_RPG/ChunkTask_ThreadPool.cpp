#pragma once
#include "ChunkTask_ThreadPool.h"
#include "ChunkTask_Thread.h"

namespace ChunkTasks {

	ChunkTask_ThreadPool::ChunkTask_ThreadPool() {
		m_threadCount = ChunkTask_ThreadPool::DEFAULT_THREAD_COUNT;

	}

	ChunkTask_ThreadPool::ChunkTask_ThreadPool(int startingThreadCount) {
		m_threadCount = startingThreadCount;
	}

	ChunkTask_ThreadPool::~ChunkTask_ThreadPool() {
		if (m_active) {
			m_active = false;
			for (int i = 0; i < m_workers.size(); i++) {
				delete m_workers[i];
			}
		}
	}
	
	void ChunkTask_ThreadPool::init() {
		if (!m_active.load()) {
			m_active.store(true);
			for (int i = 0; i < m_workers.size(); i++) {
				m_workers.push_back(new ChunkTasks::ChunkTask_Thread(this));
			}
		}
	}

	void ChunkTask_ThreadPool::addTask(ChunkTasks::ChunkTask* task) {
		{
			std::lock_guard<std::mutex> lck(m_mutex);
			m_taskQueue.push(task);
		}
		m_conditionVariable.notify_one();

	}
	//Private

	void ChunkTask_ThreadPool::_getTask(ChunkTasks::ChunkTask* task) {
		std::lock_guard<std::mutex> lck(m_mutex);
		task = m_taskQueue.front();
		if (!m_taskQueue.empty()) {
			m_taskQueue.pop();
		}
	}
}