#pragma once
#include <vector>
#include <glm\glm.hpp>
#include 

namespace  ChunkTasks {

	enum TaskType {
		MESHING, LOADING, UNLOAD
	};

	class ChunkTask {
	public:
		virtual void preTask() = 0;
		virtual void postTask() = 0;
		virtual TaskType getTaskType() = 0;
		//Only class that should be called from separate thread
		virtual void executeTask() = 0;
	};

}
