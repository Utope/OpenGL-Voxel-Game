#pragma once
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "SDL\SDL.h"
#include "StaticInput.h"
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>


/*NOTE
Pitch = up/down
Yaw = left/right
Roll = roll?
*/
class Camera {

public:
	//http://learnopengl.com/#!Getting-started/Camera

	Camera(glm::vec3 position,glm::vec3 cameraTarget, int windowWidth, int windowHeight, float fov, float nearView, float farView) {
		m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cameraPosition = position;
		m_cameraTarget = cameraTarget;
		m_cameraOppDirection = glm::normalize(m_cameraPosition - m_cameraTarget);
		m_cameraRight = glm::normalize(glm::cross(m_upVector, m_cameraTarget));
		m_cameraUp = glm::cross(m_cameraOppDirection, m_cameraRight);
		m_cameraView = glm::lookAt(m_cameraPosition,m_cameraPosition + m_cameraTarget,m_upVector);

		m_mouseLastX = (float)windowWidth;
		m_mouseLastY = (float)windowHeight;
		m_mouseSensitivity = 1.0f;

		//set up Perspective Matrix
		m_fov = fov;
		m_nearView = nearView;
		m_farView = farView;
		m_aspectRatio = (float)windowWidth / (float)windowHeight;
		m_perspective = glm::perspective(m_fov, m_aspectRatio, m_nearView, m_farView);
		m_cameraSpeed = 0.5f;

		m_pitch = 0.0f;
		m_yaw = -90.0f;
	}

	const inline glm::mat4 getMatrixView() {return m_cameraView;}
	const inline glm::mat4 getMatrixPerspective() {return m_perspective;}
	const inline glm::mat4 getMatrixVP() { return (m_perspective * m_cameraView); }

	const inline float& getFOV() {return m_fov;}
	const inline float& getNearView() {return m_nearView;}
	const inline float& getFarView() {return m_farView;}
	const inline float& getAspectRatio() {return m_aspectRatio;}

	inline void setFOV(float fov) { m_fov = fov; }
	inline void setNearView(float nearView) { m_nearView = nearView; }
	inline void setFarView(float farView) { m_farView = farView; }
	inline void setAspectRatio(int width, int height) {	m_aspectRatio = (float) width / (float) height;}
	inline void setAspectRatio(float aspectRatio) {	m_aspectRatio = aspectRatio;}

	const inline float& getPitch() { return m_pitch; }
	const inline float& getYaw() { return m_yaw; }
	const inline float& getSpeed() { return m_cameraSpeed; }

	inline void setYaw(float yaw) { m_yaw = yaw; }
	inline void setSpeed(float speed) { m_cameraSpeed = speed; }
	inline bool setPitch(float pitch) { 
		if (pitch > 89.0 || pitch < -89.0) {
			return false;
		}
		else {
			m_pitch = pitch;
			return true;
		}
	
	}

	const inline glm::vec3& getPosition() { return m_cameraPosition; }
	const inline glm::vec3& getRight() { return m_cameraRight; }
	const inline glm::vec3& getRelativeUp() { return m_cameraUp; }
	const inline glm::vec3& getTarget() { return m_cameraTarget; }



	/*
	Call after changing perspective using following functions
		setFOV(float fov) 
		setNearView(float nearView) 
		setFarView(float farView) 
		setAspectRatio(int width, int height) 
		setAspectRatio(float aspectRatio) 
	*/
	inline void updatePerspective() {
		m_perspective = m_perspective = glm::perspective(m_fov, m_aspectRatio, m_nearView, m_farView);
	}

	inline void update() {
		updateRotation(StaticInput::getMouseData().MOVEMENT_X, StaticInput::getMouseData().MOVEMENT_Y);
		m_cameraView = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraTarget, m_upVector);
		m_cameraOppDirection = glm::normalize(m_cameraPosition - m_cameraTarget);
		m_cameraRight = glm::normalize(glm::cross(m_upVector, m_cameraTarget));
		m_cameraUp = glm::cross(m_cameraTarget, m_cameraRight);

		if (StaticInput::getKeyboardData().letters.A == InputData::HELD || StaticInput::getKeyboardData().letters.A == InputData::PRESSED) {
			m_cameraPosition -= glm::normalize(glm::cross(m_cameraTarget, m_cameraUp)) * m_cameraSpeed;
		}
		
		if (StaticInput::getKeyboardData().letters.D == InputData::HELD || StaticInput::getKeyboardData().letters.D == InputData::PRESSED) {
			m_cameraPosition += glm::normalize(glm::cross(m_cameraTarget, m_cameraUp)) * m_cameraSpeed;
		}
		
		if (StaticInput::getKeyboardData().letters.W == InputData::HELD || StaticInput::getKeyboardData().letters.W == InputData::PRESSED) {
			m_cameraPosition += m_cameraTarget * m_cameraSpeed;
		}
			
		if (StaticInput::getKeyboardData().letters.S == InputData::HELD || StaticInput::getKeyboardData().letters.S == InputData::PRESSED) {
			m_cameraPosition -= m_cameraTarget * m_cameraSpeed;
		}
	}

	inline void updateRotation(int mouseXMovement, int mouseYMovement) {

		m_yaw = ((int)(m_yaw + mouseXMovement) % 360);
		m_pitch += -mouseYMovement;

		if (m_pitch > 89.0f) {
			m_pitch = 89.0f;
		}
		if (m_pitch < -89.0f) {
			m_pitch = -89.0f;
		}

		glm::vec3 cameraDir; 
		
	
		
		cameraDir.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
		cameraDir.y = sin(glm::radians(m_pitch));
		cameraDir.z = cos(glm::radians(m_pitch))*sin(glm::radians(m_yaw));

		m_cameraTarget = glm::normalize(cameraDir);

	}

	~Camera() {};

private:


	//Temporary until input handler is implemented
	float m_mouseLastX;
	float m_mouseLastY;

	float m_pitch, m_yaw;
	float m_cameraSpeed;
	float m_mouseSensitivity;

	//Perspective matrix
	float m_fov;
	float m_aspectRatio;
	float m_nearView;
	float m_farView;

	glm::mat4 m_perspective;
	glm::mat4 m_orthographic;
	glm::mat4 m_cameraView;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraUp;
	glm::vec3 m_upVector;
	glm::vec3 m_cameraTarget; // Cameras Front/Normal
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraOppDirection;

};