#pragma once
#include "Texture2D.h"
#include <vector>

class Texture2DArray {
public:
	Texture2DArray(std::string textureArrayName);
	Texture2DArray(std::string texturePaths, std::string textureArrayName);
	Texture2DArray(std::vector<std::string> texturePaths, std::string textureArrayName);
	
	int getDepth();
	int getMaxHeight();
	int getMaxWidth();
	GLuint getID();
	bool setMaxDimensions(int width, int height);
	void useCustomTextureSize(bool);
	
	GLenum getMagFilter();
	GLenum getMinFilter();
	void setMagFilter(GLenum);
	void setMinFilter(GLenum);

	GLenum getTWrap();
	GLenum getSWrap();
	void setTWrap(GLenum);
	void setSWrap(GLenum);

	void updateTextureSettings();

	bool addTexture(std::string);
	bool addTextures(std::vector<std::string> texturePaths);

	Texture2D& getTexture(std::string name);

	bool load();
	bool unLoad();

protected:
private:
	std::string m_textureArrayName;
	std::vector<Texture2D> m_containedTextures;
	GLuint m_textureArrayID;
	int m_maxHeight, m_maxWidth;
	bool m_loaded, m_useCustomSize;
	GLenum m_magFilter, m_minFilter, m_sWrap, m_tWrap;
};