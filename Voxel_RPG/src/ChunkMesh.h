#pragma once
#include <vector>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "BufferDataLoader.h"

class ChunkMesh {
public:
	//init and destroy functions
	ChunkMesh() {};
	~ChunkMesh() {};
	void setUp();
	void cleanUp();

	//Drawing functions
	unsigned int getIndices();
	void bind();
	void unBind();

	void enableAllVertexAttribArrys();
	void disableAllVertexAttribArrys();

	// Position, Normals, Colors, TextureCoords
	void enableVertexAttribArrys(bool, bool, bool, bool);

	//indices, positions, colors, normals, textureCoords... Send in nullptr if you dont want to update vbo
	void updateMesh(std::vector<unsigned int>* indices, std::vector<glm::vec3>* positions, std::vector<glm::vec3>* colors, std::vector<glm::vec3>* normals, std::vector<glm::vec2>* textureCoords);
	
private:
	GLuint m_vao;
	GLuint m_indices;
	GLuint m_vertexPositions;
	GLuint m_vertexNormals;
	GLuint m_vertexTextureCoords;
	GLuint m_vertexColors;
	unsigned int m_textureCoordsSize;
	unsigned int m_positionsSize;
	unsigned int m_indexsSize;
	unsigned int m_normalsSize;
	unsigned int m_colorsSize;

};

