#pragma once
#include "ChunkTask.h"

namespace ChunkTasks {

	class ChunkTask_Unloading : public ChunkTask {
	public:
		Chunk* chunk;
		bool success;
		ChunkTask_Unloading(Chunk* chunk) {
			this->chunk = chunk;
		}

		inline virtual void executeTask() override {
			chunk->unLoad();
		};

		inline virtual TaskType getTaskType() override {
			return TaskType::UNLOAD;
		}

		inline virtual void preTask() override {
			chunk->cleanUp();
			//Before chunk is Unloaded what all do we have to do?
		}

		inline virtual void postTask() override {

		}
	};
}