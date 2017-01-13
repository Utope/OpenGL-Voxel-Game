#pragma once
#include <vector>
#include "GL\glew.h"

class Renderer {
public:
	Renderer();
	~Renderer();
protected:
	GLuint m_vao;
	GLuint m_positionVBO;
	GLuint m_textureVBO;
	GLuint m_indexVbo;
	GLuint m_colorVBO;

	std::vector<>
	
};