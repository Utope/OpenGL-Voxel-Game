#pragma once
#include "Texture.h"
#include <string>
#include "GL\glew.h"
#include "ImageLoader.h"

GLuint Texture::getID()
{
	return m_textureID;
}
int Texture::getWidth()
{
	return m_width;
}
int Texture::getHeight()
{
	return m_height;
}
int Texture::getDepth()
{
	return 0;
}

Texture::Texture(std::string imagePath, GLenum tWrap, GLenum sWrap, GLenum minFilter, GLenum magFilter) {
	m_imagePath = imagePath;
	m_sWrap = sWrap;
	m_tWrap = tWrap;
	m_magFilter = magFilter;
	m_minFilter = minFilter;
}

std::string Texture::getImagePath() {
	return m_imagePath;
}

GLenum Texture::getMagFilter() {
	return m_magFilter;
}

GLenum Texture::getMinFilter() {
	return m_minFilter;
}

void Texture::setMagFilter(GLenum magFilter) {
	m_magFilter = magFilter;
}
void Texture::setMinFilter(GLenum minFilter) {
	m_minFilter = minFilter;
}

GLenum Texture::getTWrap() {
	return m_tWrap;
}
GLenum Texture::getSWrap() {
	return m_sWrap;
}
void Texture::setTWrap(GLenum tWrap) {
	m_tWrap = tWrap;
}
void Texture::setSWrap(GLenum sWrap) {
	m_sWrap = sWrap;
}

void Texture::load() {
	glGenTextures(1, &m_textureID);

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	unsigned char* image = ImageLoader::loadImageData(m_imagePath, &m_height, &m_width);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_tWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::unLoad() {
	glDeleteTextures(1, &m_textureID);
}

void Texture::updateTextureSettings() {
	glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_sWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_tWrap);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
