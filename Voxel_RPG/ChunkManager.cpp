#pragma once
#include "ChunkManager.h"
#include "ChunkTask_Unloading.h"
#include "ChunkTask_Loading.h"
#include "ChunkTask_Meshing.h"

ChunkManager::ChunkManager(int loadingRadius, int threadCount) {
	m_loadingRadius = loadingRadius;
	m_threadPoolRunning.store(true);
	for (int i = 0; i < threadCount; i++) {
		m_workerThreads.push_back(new std::thread(&ChunkManager::_threadHandlerFunction, this));
	}
}

ChunkManager::~ChunkManager() {
	//testing
	m_loadedChunks.insert({ glm::ivec3(0,0,0),new Chunk(glm::ivec3(0,0,0)) });
	m_loadedChunks.insert({ glm::ivec3(0,2,0),new Chunk(glm::ivec3(0,2,0)) });
	m_loadedChunks.insert({ glm::ivec3(0,3,0),new Chunk(glm::ivec3(0,3,0)) });
	if (!m_loadedChunks.empty()) {
		for (std::unordered_map<glm::ivec3, Chunk*>::iterator it = m_loadedChunks.begin(); it != m_loadedChunks.end(); ++it) {
			it->second->setUp(); // test
			it->second->load(); // test
			_addTaskToLowQ(new ChunkTasks::ChunkTask_Unloading(it->second));
		}
	}

	m_threadPoolRunning.store(false);
	m_conditionalVar.notify_all();
	for (int i = 0; i < m_workerThreads.size(); i++) {
		if (m_workerThreads[i]->joinable()) {
			m_workerThreads[i]->join();
			delete m_workerThreads[i];
		}
	}

}
//Public

void ChunkManager::setLoadingRadius(int loadingRadius) {
	m_loadingRadius = loadingRadius;
}
int ChunkManager::getLoadingRadius() {
	return m_loadingRadius;
}

void ChunkManager::update(glm::vec3 loadingPosition) {

}

//Private


//THREADING METHODS

void ChunkManager::_addTaskToHighQ(ChunkTasks::ChunkTask* task) {
	task->preTask(); //Call preTask for eachTask added
	{
		std::unique_lock<std::mutex> lock(m_queuedTaskMutex);
		m_highQ.push(task);
	}//Automatic release of lock
	m_conditionalVar.notify_one();
}

void ChunkManager::_addTaskToLowQ(ChunkTasks::ChunkTask* task) {
	task->preTask(); // Call preTask for eachTask added
	{
		std::unique_lock<std::mutex> lock(m_queuedTaskMutex);
		std::cout << "added Task to lowQ" << std::endl;
		m_lowQ.push(task);
	}//Automatic release of lock
	m_conditionalVar.notify_one();
}

void ChunkManager::_handleProccessedTasks() {
	std::vector<ChunkTasks::ChunkTask*> tasks;
	{
		std::lock_guard<std::mutex> lock(m_processedTaskMutex);

		//If numProcessed... is zero then handle ALL tasks
		if (m_numProceesedTasksHandledPerFrame == 0) {
			while (!m_processedTasks.empty()) {
				tasks.push_back(m_processedTasks.front());
				m_processedTasks.pop();
			}
		}
		else { // If its not zero handle number of tasks given
			for (int i = 0; i < m_numProceesedTasksHandledPerFrame; i++) {
				tasks.push_back(m_processedTasks.front());
				m_processedTasks.pop();
			}
		}
	}
}

//Change multiple dynamic casts to one dynamic cast to speed it up
void ChunkManager::_handleVectorOfProcessedTasks(std::vector<ChunkTasks::ChunkTask*> tasks) {
	ChunkTasks::ChunkTask* task;
	for (int i = 0; i < tasks.size(); i++) {
		//In here we handle each individual task
		task = tasks[i];
		task->postTask(); // Call postTask for each processed task

		if (task->getTaskType() == ChunkTasks::TaskType::LOADING) {
			ChunkTasks::ChunkTask_Loading* loadingTask = dynamic_cast<ChunkTasks::ChunkTask_Loading*>(task);

			m_loadedChunks[loadingTask->position] = loadingTask->chunk;

		}
		else if (task->getTaskType() == ChunkTasks::TaskType::MESHING) {
			ChunkTasks::ChunkTask_Meshing* meshingTask = dynamic_cast<ChunkTasks::ChunkTask_Meshing*>(task);
			// We send the data to each chunk for mesh processing
			//POSSIBLY CREATE ANOTHER Q FOR THIS FOR BETTER CONTROL
			m_loadedChunks[meshingTask->mapPosition]->getMesh()->updateMesh(&meshingTask->indicies, &meshingTask->positions, &meshingTask->colors, &meshingTask->normals, &meshingTask->textureCoords);
		}
		else if (task->getTaskType() == ChunkTasks::TaskType::UNLOAD) {
			ChunkTasks::ChunkTask_Unloading* unloadingTask = dynamic_cast<ChunkTasks::ChunkTask_Unloading*>(task);
			delete m_loadedChunks.find(unloadingTask->chunk->getPosition())->second;
			m_loadedChunks.erase(unloadingTask->chunk->getPosition());

		}
		else {
			assert(false && "A defined task was not called");
		}

		//And delete it
		delete task;
		task = nullptr;
	}
}

void ChunkManager::_threadHandlerFunction() {
	ChunkTasks::ChunkTask* task = nullptr;

	while (m_threadPoolRunning.load()) {
		{
			std::unique_lock<std::mutex> lock(m_queuedTaskMutex);
			while (m_threadPoolRunning.load() && m_lowQ.empty() && m_highQ.empty()) {
				m_conditionalVar.wait(lock);
			}

			if (!m_highQ.empty()) {
				task = m_highQ.front();
				m_highQ.pop();
			}
			else if (!m_lowQ.empty()) {
				task = m_lowQ.front();
				m_lowQ.pop();
			}
		}//Release m_queuedTaskMutex Lock
		if (task != nullptr) {
			task->executeTask();

			{
				std::unique_lock<std::mutex> lock(m_processedTaskMutex);
				m_processedTasks.push(task);
			}//Release m_processedTask Lock;

			task = nullptr;
		}

	}
}
