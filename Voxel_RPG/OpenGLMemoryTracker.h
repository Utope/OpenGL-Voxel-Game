#pragma once
#include<vector>
#include<GL\glew.h>

class OpenGLMemoryTracker {
public:

	static GLuint AllocateTexture();
	static GLuint AllocateVao();
	static GLuint AllocateVbo();
	static void DeAllocateTexture(GLuint texture);
	static void DeAllocateVao(GLuint vao);
	static void DeAllocateVbo(GLuint vbo);
	
	static void CleanUp();

	static std::vector<GLuint> m_vboAllocations;
	static std::vector<GLuint> m_vaoAllocations;
	static std::vector<GLuint> m_textureAllocations;

private:
	friend OpenGLMemoryTracker;

};