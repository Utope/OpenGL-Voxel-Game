#pragma once
#include "GLCamera.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

const glm::vec3 GLCamera::WORLD_UP_VECTOR = glm::vec3(0.0, 1.0, 0.0);

GLCamera::GLCamera(glm::vec3& position, glm::vec3& target, unsigned int windowWidth, unsigned int windowHeight, float fov, float nearView, float farView) {
	m_position = position;
	m_forward = glm::normalize(target - position);
	m_right = glm::cross(m_forward, GLCamera::WORLD_UP_VECTOR);
	m_localUp = glm::cross(m_right, m_forward);
}
GLCamera::~GLCamera() {

}

void GLCamera::update() {
	/*
	glm::quat quatX = (glm::vec3(1.0, 0.0, 0.0),);
	glm::quat quatY = (glm::vec3(0.0, 1.0, 0.0),);
	glm::quat quatZ = (glm::vec3(0.0, 0.0, 1.0),);

	glm::quat quatXYZ = quatX * quatY * quatZ;
	*/
}

float GLCamera::getNearView() {
	return m_nearview;
}
float GLCamera::getFarView() {
	return m_farview;
}
const glm::vec3& GLCamera::getForward() {
	return m_forward;
}
float GLCamera::getAspectRatio() {
	return (float)m_windowWidth / (float)m_windowHeight;
}
float GLCamera::getFOV() {
	return m_fov;
}
const glm::vec3& GLCamera::getLocalUp() {
	return m_localUp;
}
const glm::vec3& GLCamera::getPosition() {
	return m_position;
}
void GLCamera::setforward(glm::vec3& forward) {
	m_forward = forward;
}
void GLCamera::setPosition(glm::vec3& position) {
	m_position = position;
}
const glm::vec3& GLCamera::getRight() {
	return m_right;
}
unsigned int GLCamera::getWindowHeight() {
	return m_windowHeight;
}
unsigned int GLCamera::getWindowWidth() {
	return m_windowWidth;
}
void GLCamera::setWindowDimensions(unsigned int width, unsigned int height) {
	m_windowWidth = width;
	m_windowHeight = height;
}
void GLCamera::setFOV(float fov) {
	m_fov = fov;
}
void GLCamera::setNearFarView(float near, float far) {
	m_nearview = near;
	m_farview = far;
}
void GLCamera::setRotation(float x, float y, float z) {
	m_eulersAngles = glm::vec3(x, y, z);
}
glm::vec3& GLCamera::getRotations() {
	return m_eulersAngles;
}

