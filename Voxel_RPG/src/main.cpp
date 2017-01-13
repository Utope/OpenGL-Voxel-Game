#include "Display.h"
#include "GL\glew.h"
#include <iostream>
#include <vector>
#include "Camera.h"
#include "glm\glm.hpp"
#include "noise\noise.h"
#include "FPS.h"
#include "Texture.h"
#include "Shader.h"
#include "OpenGLMemoryTracker.h"
#include "StaticInput.h"
#include "ArrayTexture.h"
#include "Texture.h"
#include "Timer.h"
#define WIDTH 640
#define HEIGHT 480

/*
FPS/ms counter
Update my display class
Update camera class
Possibly input multiplexer
Render Class :D!
*/

int main(int argc, char** argv) {


	Display display(WIDTH, HEIGHT, "Hey!");

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(display.getSDL_WindowPointer(), WIDTH / 2, HEIGHT / 2);

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT, 70.0f, 0.1f, 1000.0f);

	FPS fps;
	fps.init();

	bool mouseDrag = false;

	int nbFrames = 0;
	double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	bool blockupdate = false;

	glm::vec3 positionCoords[]{
		glm::vec3(10.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 10.0, 0.0),

		glm::vec3(0.0, 10.0, 0.0),
		glm::vec3(10.0, 10.0, 0.0),
		glm::vec3(10.0, 0.0, 0.0)
	};

	glm::vec3 textureCoords[]{
		glm::vec3(0.0,1.0,1.0),
		glm::vec3(0.0, 0.0,1.0),
		glm::vec3(1.0,0.0,1.0),

		glm::vec3(1.0,0.0,1.0),
		glm::vec3(1.0,1.0,1.0),
		glm::vec3(0.0,1.0,1.0)
	};

	GLuint vao = OpenGLMemoryTracker::AllocateVao();
	GLuint texVbo = OpenGLMemoryTracker::AllocateVbo();
	GLuint posVbo = OpenGLMemoryTracker::AllocateVbo();

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &positionCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texVbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &textureCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	
	Shader shaderTest({ "..\\resources\\Shaders\\TextureShader.vs","..\\resources\\Shaders\\TextureShader.fs" });
	shaderTest.load();
	shaderTest.link();

	Shader shaderArrayTest({ "..\\resources\\Shaders\\TextureArrayShader.vs","..\\resources\\Shaders\\TextureArrayShader.fs" });
	shaderArrayTest.load();
	shaderArrayTest.link();

	ArrayTexture aryTex(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER,GL_NEAREST,GL_NEAREST);
	aryTex.addImagePaths("..\\resources\\images\\healer_1.png");
	aryTex.addImagePaths("..\\resources\\images\\healer_2.png");
	//aryTex.addImagePaths("..\\resources\\images\\healer_2.png");
	aryTex.load();

	Texture tex2D("..\\resources\\images\\DragonIcon.png", GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_LINEAR, GL_LINEAR);
	tex2D.load();

	Timer timer;
	timer.start();

	double i = 0.0;
	int spriteCounter = 0;
	while (!display.IsClosed()) {
		display.Clear(0.0, 0.0, 0.0, 0.0);
		StaticInput::update();
		fps.limit();
		camera.update();
		if (StaticInput::getMouseData().LEFT_CLICK == InputData::PRESSED) {
			//spriteCounter++;
		}
		
		if (timer.milliseconds() > 100) {
			spriteCounter++;
			timer.updateStart();
		}

		shaderArrayTest.bind();
		glBindVertexArray(vao);

		shaderArrayTest.loadMat4x4(0, false, camera.getMatrixVP());
		shaderArrayTest.loadFloat(1, (float)(spriteCounter%2));
		
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
		glBindTexture(GL_TEXTURE_2D_ARRAY, aryTex.getID());
	
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		shaderArrayTest.unBind();
		
		display.Update();
		i+=0.01;

	}
	timer.stop();
	std::cout << timer.milliseconds() << std::endl;
	OpenGLMemoryTracker::CleanUp();

	return 0;
}
