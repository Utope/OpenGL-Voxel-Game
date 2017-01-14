#pragma once
#include "GL\glew.h"
#include <string>

class Texture2D {
public:
	Texture2D(int width, int height, int depth, std::string path, std::string name);
	Texture2D();
	int getWidth();
	int getHeight();
	int getDepth();

	std::string getPath();
	std::string getName();
	
protected:
private:
	friend class Texture2DArray;
		void _setHeight(int height);
		void _setWidth(int width);
		void _setDepth(int depth);
		void _setTextureArray(Texture2DArray* texture2DArray);
		void _setPath(std::string path);
		void _setName(std::string name);

	std::string m_name;
	std::string m_path;
	Texture2DArray* m_textureArray;
	int m_depth,m_height,m_width;
};