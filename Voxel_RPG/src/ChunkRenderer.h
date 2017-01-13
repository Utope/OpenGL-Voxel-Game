#pragma once
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "DebugShader_Positions_Colors.h"
#include <vector>
#include <iostream>
#include "GLSL_ShaderProgram.h"

struct MeshData{
	GLuint meshID_VAO;
	GLuint position_VBO;
	GLuint color_VBO;
	GLuint indices_VBO;
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec3> vertexColors;
	std::vector<unsigned int> vertexIndices;
};

struct TextureMesh_Data {
	GLuint meshID_VAO;
	GLuint position_VBO;
	GLuint color_VBO;
	GLuint indices_VBO;
	GLuint textureCoords_VBO;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec3> vertexColors;
	std::vector<unsigned int> vertexIndices;
};

class ChunkRenderer {
public:
	ChunkRenderer();
	~ChunkRenderer();

	MeshData* createMesh();
	void deleteMesh(MeshData* pmeshData);

	void startEditingMesh(MeshData* pmeshID);
	void addTriangle(MeshData* pmeshID, unsigned int vert1, unsigned int vert2, unsigned int vert3);
	void addVertex(MeshData* pmeshID, glm::vec3 position, glm::vec3 color);
	void stopEditingMesh(MeshData* pmeshID);

	void render();

private:
	std::vector<MeshData*> m_meshData;
	GLuint currentlyBound_VAO;
	void flushMeshData(MeshData* pmeshID);
	void clearMeshDataBuffers(MeshData* pmeshID);
};
