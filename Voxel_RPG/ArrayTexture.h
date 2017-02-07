#pragma once
#include <string>
#include "GLTexture.h"

class ArrayTexture : public GLTexture  {
public:
	
	GLuint getID();
	int getWidth();
	int getHeight();
	int getDepth();
	void load();
	void unLoad();

	ArrayTexture(std::vector<std::string>, GLenum uWrap, GLenum vWrap, GLenum magFilter, GLenum minFilter);
	ArrayTexture(GLenum uWrap, GLenum vWrap, GLenum magFilter, GLenum minFilter);
	
	void addImages(std::string);
	void addImages(std::vector<std::string>);
	std::vector<std::string>& getImagePaths();
	
	GLenum getMagFilter();
	GLenum getMinFilter();
	void setMagFilter(GLenum);
	void setMinFilter(GLenum);

	GLenum getTWrap();
	GLenum getSWrap();
	void setTWrap(GLenum);
	void setSWrap(GLenum);

	void updateTextureSettings();

	void setMaxHeight();
	void setMaxWidth();

protected:
	std::vector<std::string> m_imagePaths;
	GLuint m_textureID;
	GLenum m_magFilter;
	GLenum m_minFilter;
	GLenum m_sWrap;
	GLenum m_tWrap;
	int m_width, m_height, m_depth;
};