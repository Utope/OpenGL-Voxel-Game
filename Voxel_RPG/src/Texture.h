#pragma once
#include <string>
#include<vector>
#include <map>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "GLTexture.h"

class Texture : public GLTexture {
public:
	
	GLuint getID() = 0;
	int getWidth() = 0;
	int getHeight() = 0;
	int getDepth() = 0;
	void load() = 0;
	void unLoad() = 0;
	
	Texture(std::string imagepath, GLenum tWrap, GLenum sWrap, GLenum magFilter, GLenum minFilter );

	std::string getImagePath();

	GLenum getMagFilter();
	GLenum getMinFilter();
	void setMagFilter(GLenum);
	void setMinFilter(GLenum);

	GLenum getTWrap();
	GLenum getSWrap();
	void setTWrap(GLenum);
	void setSWrap(GLenum);

	void updateTextureSettings();

	
private:
	std::string m_imagePath;
	GLuint m_textureID;
	GLenum m_magFilter;
	GLenum m_minFilter;
	GLenum m_sWrap;
	GLenum m_tWrap;
	int m_width, m_height;
};