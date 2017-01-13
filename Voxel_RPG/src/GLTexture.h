#pragma once
#include <string>
#include <vector>
#include "GL\glew.h"

class GLTexture {
public:

	virtual GLuint getID() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0; 
	virtual int getDepth() = 0;
	virtual void load() = 0;
	virtual void unLoad() = 0;
};