#include "Texture2DArray.h"
#include "ImageLoader.h"

Texture2DArray::Texture2DArray(std::string textureArrayName)
{
	m_magFilter = GL_NEAREST;
	m_minFilter = GL_NEAREST;
	m_sWrap = GL_CLAMP_TO_BORDER;
	m_tWrap = GL_CLAMP_TO_BORDER;
	m_maxHeight = -1;
	m_maxWidth = -1;
	m_loaded = false;
	m_textureArrayName = textureArrayName;
}

Texture2DArray::Texture2DArray(std::string texturePath, std::string textureArrayName)
{
	m_magFilter = GL_NEAREST;
	m_minFilter = GL_NEAREST;
	m_sWrap = GL_CLAMP_TO_BORDER;
	m_tWrap = GL_CLAMP_TO_BORDER;
	m_maxHeight = -1;
	m_maxWidth = -1;
	m_loaded = false;
	m_textureArrayName = textureArrayName;
	this->addTexture(texturePath);
}

Texture2DArray::Texture2DArray(std::vector<std::string> texturePaths, std::string textureArrayName)
{
	m_magFilter = GL_NEAREST;
	m_minFilter = GL_NEAREST;
	m_sWrap = GL_CLAMP_TO_BORDER;
	m_tWrap = GL_CLAMP_TO_BORDER;
	m_maxHeight = -1;
	m_maxWidth = -1;
	m_loaded = false;
	m_textureArrayName = textureArrayName;
	this->addTextures(texturePaths);
}

int Texture2DArray::getDepth()
{
	return m_containedTextures.size();
}

int Texture2DArray::getMaxHeight()
{
	return m_maxHeight;
}

int Texture2DArray::getMaxWidth()
{
	return m_maxWidth;
}

GLuint Texture2DArray::getID()
{
	return m_textureArrayID;
}

bool Texture2DArray::setMaxDimensions(int width,int height)
{
	if (!m_loaded) {
		m_maxWidth = width;
		m_maxHeight = height;
		return true;
	}
	else {
		return false;
	}
}

void Texture2DArray::useCustomTextureSize(bool value)
{
	m_useCustomSize = value;
}

GLenum Texture2DArray::getMagFilter()
{
	return m_magFilter;
}

GLenum Texture2DArray::getMinFilter()
{
	return m_minFilter;
}

void Texture2DArray::setMagFilter(GLenum magFilter)
{
	m_magFilter = magFilter;
}

void Texture2DArray::setMinFilter(GLenum minFilter)
{
	m_minFilter = minFilter;
}

GLenum Texture2DArray::getTWrap()
{
	return m_tWrap;
}

GLenum Texture2DArray::getSWrap()
{
	return m_sWrap;
}

void Texture2DArray::setTWrap(GLenum tWrap)
{
	m_tWrap = tWrap;
}

void Texture2DArray::setSWrap(GLenum sWrap)
{
	m_sWrap = sWrap;
}

void Texture2DArray::updateTextureSettings()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArrayID);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, m_magFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, m_sWrap);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, m_tWrap);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArrayID);
}

bool Texture2DArray::addTexture(std::string texturePath)
{
	if (!m_loaded) {
		m_containedTextures.push_back(Texture2D());
		m_containedTextures[m_containedTextures.size() - 1]._setPath(texturePath);
		m_containedTextures[m_containedTextures.size() - 1]._setTextureArray(this);
		return true;
	}
	else {
		return false;
	}
	
}

bool Texture2DArray::addTextures(std::vector<std::string> texturePaths)
{
	if (!m_loaded) {
		for (int i = 0; i < texturePaths.size(); i++) {
			this->addTexture(texturePaths[i]);
		}
		return true;
	}
	else {
		return false;
	}
	
}

//TODO
Texture2D & Texture2DArray::getTexture(std::string name)
{
	return Texture2D();
}

bool Texture2DArray::load()
{
	struct ImageData{
		
		int u;
		int v;
		int comp;
		unsigned char* data;
	};

	if (!m_containedTextures.empty()) {

		glGenTextures(1, &m_textureArrayID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArrayID);

		std::vector<ImageData> imageData;
		imageData.reserve(m_containedTextures.size());

		for (int i = 0; i < m_containedTextures.size(); i++) {
			imageData.push_back(ImageData());
			imageData[i].data = ImageLoader::loadImageData(m_containedTextures[i].getPath(), &imageData[i].u, &imageData[i].v, &imageData[i].comp);
			m_containedTextures[i]._setWidth(imageData[i].u);
			m_containedTextures[i]._setHeight(imageData[i].v);
			m_containedTextures[i]._setDepth(i);
		
		}

		if (!m_useCustomSize || m_maxHeight < 0 || m_maxWidth < 0) {
			int maxU = 0;
			int maxV = 0;
			for (int i = 0; i < imageData.size(); i++) {
				if (imageData[i].u > maxU) {
					maxU = imageData[i].u;
				}
				if (imageData[i].v > maxV) {
					maxV = imageData[i].v;
				}
			}

			m_maxHeight = maxV;
			m_maxWidth = maxU;

		}

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, m_maxWidth, m_maxHeight, m_containedTextures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		for (int i = 0; i < m_containedTextures.size(); i++) {
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0 , i, imageData[i].u, imageData[i].v, 1, GL_RGBA, GL_UNSIGNED_BYTE, imageData[i].data);
			ImageLoader::freeImageData(imageData[i].data);
		}

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, m_magFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, m_sWrap);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, m_tWrap);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

		m_loaded = true;
		return true;
	}
	//Empty return false
	return false;
}

bool Texture2DArray::unLoad()
{
	if (m_loaded) {
		glDeleteTextures(1, &m_textureArrayID);
		m_loaded = false;
		return true;
	}
	else {
		return false;
	}
}
