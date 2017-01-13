#pragma once
#include <string>
#include "GLTexture.h"

class ArrayTexture : public GLTexture  {
public:
	
	// Inherited via GLTexture
	virtual GLuint getID() override;
	virtual int getWidth() override;
	virtual int getHeight() override;
	virtual int getDepth() override;
	virtual void load() override;
	virtual void unLoad() override;

	ArrayTexture(std::vector<std::string>, GLenum uWrap, GLenum vWrap, GLenum magFilter, GLenum minFilter);
	ArrayTexture(GLenum uWrap, GLenum vWrap, GLenum magFilter, GLenum minFilter);
	
	void addImagePaths(std::string);
	void addImagePaths(std::vector<std::string>);
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

protected:
	std::vector<std::string> m_imagePaths;
	GLuint m_textureID;
	GLenum m_magFilter;
	GLenum m_minFilter;
	GLenum m_sWrap;
	GLenum m_tWrap;
	int m_width, m_height, m_depth;
};