#pragma once
#include "ChunkTask.h"

namespace ChunkTasks {

	class ChunkTask_Loading : public ChunkTask {
	public:

		Chunk* chunk;
		glm::ivec3 position;

		ChunkTask_Loading(glm::ivec3 position) {
			this->position = position;
			chunk = nullptr;
		}

		inline virtual void executeTask() override {
			chunk = new Chunk(position);
			std::cout << "creation" << std::endl;
		};

		inline virtual TaskType getTaskType() override {
			return TaskType::LOADING;
		}

		inline virtual void preTask() override {
			//Before chunk is loaded what all do we have to do?
			chunk->setUp();
		}

		inline virtual void postTask() override {

		}

	};
}