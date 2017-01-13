#include "ArrayTexture.h"
#include "TextureLoader.h"
#include "ImageLoader.h"

//Inherited by GLTexture
GLuint ArrayTexture::getID()
{
	return m_textureID;
}
int ArrayTexture::getWidth()
{
	return m_width;
}
int ArrayTexture::getHeight()
{
	return m_height;
}
int ArrayTexture::getDepth(){
	return m_depth;
}

//Constructor(s) and deconstructor
ArrayTexture::ArrayTexture(std::vector<std::string> imagePaths, GLenum uWrap, GLenum vWrap, GLenum magFilter, GLenum minFilter) {
	m_width = 0;
	m_height = 0;
	m_imagePaths = imagePaths;
	m_depth = m_imagePaths.size();
	m_sWrap = uWrap;
	m_tWrap = vWrap;
	m_magFilter = magFilter;
	m_minFilter = minFilter;
}
ArrayTexture::ArrayTexture(GLenum uWrap, GLenum vWrap, GLenum magFilter, GLenum minFilter) {
	m_textureID = 0;
	m_depth = 0;
	m_width = 0;
	m_height = 0;
	m_sWrap = uWrap;
	m_tWrap = vWrap;
	m_magFilter = magFilter;
	m_minFilter = minFilter;
}

void ArrayTexture::addImagePaths(std::string newPath) {
	m_imagePaths.push_back(newPath);
	m_depth = m_imagePaths.size();
}

void ArrayTexture::addImagePaths(std::vector<std::string> newPaths) {
	for (unsigned int i = 0; i < newPaths.size(); i++) {
		m_imagePaths.push_back(newPaths[i]);
	}
	m_depth = m_imagePaths.size();
}

std::vector<std::string>& ArrayTexture::getImagePaths() {
	return m_imagePaths;
}

void ArrayTexture::setMagFilter(GLenum magFilter) {
	m_magFilter = magFilter;
}

void ArrayTexture::setMinFilter(GLenum minFilter) {
	m_minFilter = minFilter;
}

GLenum ArrayTexture::getMinFilter() {
	return m_minFilter;
}

GLenum ArrayTexture::getMagFilter() {
	return m_magFilter;
}

void ArrayTexture::setSWrap(GLenum sWrap) {
	m_sWrap = sWrap;
}

void ArrayTexture::setTWrap(GLenum tWrap) {
	m_tWrap = tWrap;
}

GLenum ArrayTexture::getTWrap() {
	return m_tWrap;
}

GLenum ArrayTexture::getSWrap() {
	return m_sWrap;
}

void ArrayTexture::load() {

	if (!m_imagePaths.empty()) {
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID);
		
		//First chunk sets first image and max size
		unsigned char* image = ImageLoader::loadImageData(m_imagePaths[0], &m_width, &m_height);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, m_width, m_height, m_imagePaths.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, m_width, m_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
		ImageLoader::freeImageData(image);

		for (unsigned int i = 1; i < m_imagePaths.size(); i++) {
			int u, v, comp;
			unsigned char* image = ImageLoader::loadImageData(m_imagePaths[i], &u, &v, &comp);
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, u, v, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
			ImageLoader::freeImageData(image);
		}

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, m_magFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S, m_sWrap);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, m_tWrap);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}
}

void ArrayTexture::unLoad() {
	glDeleteTextures(1, &m_textureID);
}

void ArrayTexture::updateTextureSettings() {
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, m_magFilter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, m_sWrap);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, m_tWrap);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID);
}