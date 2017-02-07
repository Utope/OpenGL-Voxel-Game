#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "GL\glew.h"

class BufferDataLoader {
public:

	static void loadIndicies(GLuint vbo, std::vector<unsigned int>* indices, unsigned int previousSize);
	static void loadIndicies(GLuint vbo, std::vector<unsigned short>* indices, unsigned int previousSize);

	//Floats
	static void LoadDataIntoAttribArray(GLuint vbo, std::vector<glm::vec3>* data, unsigned int previousSize);
	static void LoadDataIntoAttribArray(GLuint vbo, std::vector<glm::vec2>* data, unsigned int previousSize);
	static void LoadDataIntoAttribArray(GLuint vbo, std::vector<float>* data, unsigned int previousSize);
	
	//Ints
	
	//Shorts

	//Bytes

	//Unsigned Ints

	//Unsigned Shorts

	//Unsigned bytes

};