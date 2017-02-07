#pragma once
#include "glm\glm.hpp"
#include "GLTexture.h"

class Sprite {
public:
	Sprite(glm::vec3 pos, GLTexture* texture, float textureDepth, float scale, glm::vec3 color);
	~Sprite();
protected:
	glm::vec3 m_texCoords[4];
	glm::vec3 m_position;
	float m_scale;
	glm::vec3 m_color;
	GLTexture* m_texture;
};