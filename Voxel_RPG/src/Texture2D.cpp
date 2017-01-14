#include "Texture2D.h"

Texture2D::Texture2D(int width, int height, int depth, std::string path, std::string name)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_path = path;
	m_name = name;
}

Texture2D::Texture2D()
{
}

int Texture2D::getWidth()
{
	return m_width;
}

int Texture2D::getHeight()
{
	return m_height;
}

int Texture2D::getDepth()
{
	return m_depth;
}

std::string Texture2D::getPath()
{
	return m_path;
}

std::string Texture2D::getName()
{
	return m_name;
}

void Texture2D::_setHeight(int height)
{
	m_height = height;
}

void Texture2D::_setWidth(int width)
{
	m_width = width;
}

void Texture2D::_setDepth(int depth)
{
	m_depth = depth;
}

void Texture2D::_setTextureArray(Texture2DArray * texture2DArray)
{
	m_textureArray = texture2DArray;
}

void Texture2D::_setPath(std::string path)
{
	m_path = path;
}

void Texture2D::_setName(std::string name)
{
	m_name = name;
}
