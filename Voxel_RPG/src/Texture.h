#pragma once
#include <string>
#include<vector>
#include <map>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "GLTexture.h"

class Texture : public GLTexture {
public:
	// Inherited via GLTexture
	virtual GLuint getID() override;
	virtual int getWidth() override;
	virtual int getHeight() override;
	virtual int getDepth() override;
	virtual void load() override;
	virtual void unLoad() override;
	
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