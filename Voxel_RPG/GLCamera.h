#pragma once
#include "glm\glm.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtc\quaternion.hpp"

class GLCamera {
public: 
	static const glm::vec3 WORLD_UP_VECTOR;

	GLCamera(glm::vec3& position, glm::vec3& target, unsigned int windowWidth, unsigned int windowHeight, float fov, float nearView, float farView);
	~GLCamera();

	void setPosition(glm::vec3&);
	void setforward(glm::vec3&);

	const glm::mat4x4& getView();
	const glm::mat4x4& getOrthographic();
	const glm::mat4x4& getPerspective();

	float getAspectRatio();
	const glm::vec3& getPosition();
	const glm::vec3& getForward();
	const glm::vec3& getLocalUp();
	const glm::vec3& getRight();

	void update();

	unsigned int getWindowHeight();
	unsigned int getWindowWidth();
	void setWindowDimensions(unsigned int width, unsigned int height);
	void setFOV(float fov);
	void setNearFarView(float near, float far);

	void setRotation(float x,float y,float z);
	glm::vec3& getRotations();

	float getFOV();
	float getNearView();
	float getFarView();

private:
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_localUp;
	glm::vec3 m_right;
	glm::quat m_quat;
	glm::vec3 m_eulersAngles;
	unsigned int m_windowHeight, m_windowWidth;
	float m_fov, m_nearview, m_farview;
};