#pragma once

#include "SDL\SDL.h"
#include <string>
#include <iostream>
#include "Timer.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float b, float g, float a);
	void Update();
	void prepare();
	bool IsClosed();
	Timer& getDisplayTimer();
	void setClearColor(float r, float b, float g, float a);
	void GetDisplayDimensions(int* w, int* h) { 
		SDL_GetWindowSize(m_window, w, h);
	};

	void Close() { m_isClosed = true; };
	SDL_Window* getSDL_WindowPointer() { return m_window; };
	~Display();
protected:
private:
	int height;
	int width;
	Timer m_displayTimer;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	int r, g, b, a;
	bool m_isClosed;
};

