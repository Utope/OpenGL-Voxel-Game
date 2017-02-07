#include "OpenGLMemoryTracker.h"
#include <algorithm>
#include <iterator>
// Static Variables
std::vector<GLuint> OpenGLMemoryTracker::m_vboAllocations = std::vector<GLuint>();
std::vector<GLuint> OpenGLMemoryTracker::m_vaoAllocations = std::vector<GLuint>();
std::vector<GLuint> OpenGLMemoryTracker::m_textureAllocations = std::vector<GLuint>();

/*
Allocates Texture Buffers. returns a pointer of newly allocated Texture Buffers (numVaos)
*/
GLuint OpenGLMemoryTracker::AllocateTexture() {
	
	GLuint textureBuffer;
	glGenTextures(1, &textureBuffer);
	OpenGLMemoryTracker::m_textureAllocations.push_back(textureBuffer);
	return textureBuffer;
}

/*
Allocates Vaos. returns a pointer of newly allocated Vaos (numVaos)
*/
GLuint OpenGLMemoryTracker::AllocateVao()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	m_vboAllocations.push_back(vao);
	return vao;
}
/*
Allocates Vaos. returns a pointer of newly allocated Vbos (numVaos)
*/
GLuint OpenGLMemoryTracker::AllocateVbo()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	m_vboAllocations.push_back(vbo);
	return vbo;
}

/*
Deallocates texture Buffers. (GLuint*, numTextureBuffers)
- No check for wrong OpenGL memory being deleted
*/
void OpenGLMemoryTracker::DeAllocateTexture(GLuint textureBuffer)
{
	std::vector<GLuint>::iterator it;
	it = std::find(OpenGLMemoryTracker::m_textureAllocations.begin(), OpenGLMemoryTracker::m_textureAllocations.end(),textureBuffer);
	
	if (it != m_textureAllocations.end()) {
		m_textureAllocations.erase(it);
	}
	
	glDeleteTextures(1, &textureBuffer);
}
/*
Deallocates Vaos. (GLuint*, numVaos)
- No check for wrong OpenGL memory being deleted
*/
void OpenGLMemoryTracker::DeAllocateVao(GLuint vao)
{
	std::vector<GLuint>::iterator it;
	it = std::find(m_vaoAllocations.begin(), m_vaoAllocations.end(), vao);

	if (it != m_vaoAllocations.end()) {
		m_vaoAllocations.erase(it);
	}
	
	glDeleteTextures(1, &vao);
}

/*
Deallocates Vbos. (GLuint*, numVbos)
- No check for wrong OpenGL memory being deleted
*/
void OpenGLMemoryTracker::DeAllocateVbo(GLuint vbo)
{
	std::vector<GLuint>::iterator it;
	it = std::find(m_vboAllocations.begin(), m_vboAllocations.end(), vbo);

	if (it != m_vboAllocations.end()) {
		m_vboAllocations.erase(it);
	}
	
	glDeleteTextures(1, &vbo);
}

/*
Tells OpenGL to deallocate all memory allocated.
-Always call at end of program
*/
void OpenGLMemoryTracker::CleanUp()
{
	
	for (unsigned int i = 0; i < m_textureAllocations.size(); i++) {
		glDeleteTextures(1, &m_textureAllocations[i]);
	}

	for (unsigned int i = 0; i < m_vboAllocations.size(); i++) {
		glDeleteBuffers(1, &m_vboAllocations[i]);
	}

	for (unsigned int i = 0; i < m_vaoAllocations.size(); i++) {
		glDeleteVertexArrays(1, &m_vaoAllocations[i]);
	}

	m_textureAllocations.clear();
	m_vboAllocations.clear();
	m_vaoAllocations.clear();
		
}
