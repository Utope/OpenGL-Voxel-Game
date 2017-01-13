#pragma once
#include "GL\glew.h"
#include <string>
#include <vector>

class TextureLoader {
	
public:
/*
	static void Load2DTexture(Texture& texture);
	static void LoadCubeMapTexture(Texture& texture);
	static GLuint Load2DTextureArray(std::vector<std::string>, int, int);
	static void DeleteTexture(Texture& texture);
*/
	static GLenum getDefaultMagFilter();
	static GLenum getDefaultMinFilter();
	static GLenum getDefaultUWrap();
	static GLenum getDefaultVWrap();

	static GLenum getDefaultTWrap();
	static GLenum getDefaultSWrap();
	static GLenum getDefaultRWrap();

	static void setDefaultTWrap(GLenum);
	static void getDefaultSWrap(GLenum);
	static void getDefaultRWrap(GLenum);

	static void setDefaultMagFilter(GLenum);
	static void setDefaultMinFilter(GLenum);
	static void setDefaultUWrap(GLenum);
	static void setDefaultVWrap(GLenum);

protected:
private:
	static GLenum DEFAULT_T_WRAP;
	static GLenum DEFAULT_S_WRAP;
	static GLenum DEFAULT_R_WRAP;

	static GLenum DEFAULT_MAG_FILTER;
	static GLenum DEFAULT_MIN_FILTER;
	static GLenum DEFAULT_U_WRAP;
	static GLenum DEFAUKT_V_WRAP;
};