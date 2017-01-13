#pragma once
#include "ChunkTask.h"

namespace ChunkTasks {

	class ChunkTask_Meshing : public ChunkTask {
	public:

		//Chunk mesh goes here
		std::vector<unsigned int> indicies;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
		glm::ivec3 mapPosition;

		int offset;
		//Need to copy only neccesary data
		ChunkTask_Meshing(int offset, glm::ivec3 position) {
			this->offset = offset;
			mapPosition = position;
		}

		inline virtual void executeTask() override {
			greedy();
			std::cout << "greedy" << std::endl;
		};

		inline virtual TaskType getTaskType() override {
			return TaskType::MESHING;
		}

		inline virtual void preTask() override {

		}

		inline virtual void postTask() override {

		}

		inline void greedy() {};

	};
}