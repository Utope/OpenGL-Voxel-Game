#pragma once
#include "StaticInput.h"
#include <iostream>

InputData StaticInput::m_inputData;

void StaticInput::update() {
	SDL_Event e;
	StaticInput::_prepInput();
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			StaticInput::_keyboardEvent(e);
		}
		else if (e.type == SDL_WINDOWEVENT) {
			StaticInput::_windowEvent(e);
		}
		else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || 
				e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEWHEEL) {
			StaticInput::_mouseEvent(e);
		}
	}
}

InputData::KeyboardData& StaticInput::getKeyboardData() {
	return m_inputData.keyboardData;
}

InputData::MouseData& StaticInput::getMouseData() {
	return m_inputData.mouseData;
}

void StaticInput::_prepInput() {
	//Keyboard Prep
	if (m_inputData.keyboardData.letters.A == InputData::PRESSED) {
		m_inputData.keyboardData.letters.A = InputData::HELD;
	}
	else if(m_inputData.keyboardData.letters.A == InputData::RELEASED) {
		m_inputData.keyboardData.letters.A = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.B == InputData::PRESSED) {
		m_inputData.keyboardData.letters.B = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.B == InputData::RELEASED) {
		m_inputData.keyboardData.letters.B = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.C == InputData::PRESSED) {
		m_inputData.keyboardData.letters.C = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.C == InputData::RELEASED) {
		m_inputData.keyboardData.letters.C = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.D == InputData::PRESSED) {
		m_inputData.keyboardData.letters.D = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.D == InputData::RELEASED) {
		m_inputData.keyboardData.letters.D = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.E == InputData::PRESSED) {
		m_inputData.keyboardData.letters.E = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.E == InputData::RELEASED) {
		m_inputData.keyboardData.letters.E = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.F == InputData::PRESSED) {
		m_inputData.keyboardData.letters.F = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.F == InputData::RELEASED) {
		m_inputData.keyboardData.letters.F = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.G == InputData::PRESSED) {
		m_inputData.keyboardData.letters.G = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.G == InputData::RELEASED) {
		m_inputData.keyboardData.letters.G = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.H == InputData::PRESSED) {
		m_inputData.keyboardData.letters.H = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.H == InputData::RELEASED) {
		m_inputData.keyboardData.letters.H = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.I == InputData::PRESSED) {
		m_inputData.keyboardData.letters.I = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.I == InputData::RELEASED) {
		m_inputData.keyboardData.letters.I = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.J == InputData::PRESSED) {
		m_inputData.keyboardData.letters.J = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.J == InputData::RELEASED) {
		m_inputData.keyboardData.letters.J = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.K == InputData::PRESSED) {
		m_inputData.keyboardData.letters.K = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.K == InputData::RELEASED) {
		m_inputData.keyboardData.letters.K = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.L == InputData::PRESSED) {
		m_inputData.keyboardData.letters.L = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.L == InputData::RELEASED) {
		m_inputData.keyboardData.letters.L = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.M == InputData::PRESSED) {
		m_inputData.keyboardData.letters.M = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.M == InputData::RELEASED) {
		m_inputData.keyboardData.letters.M = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.N == InputData::PRESSED) {
		m_inputData.keyboardData.letters.N = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.N == InputData::RELEASED) {
		m_inputData.keyboardData.letters.N = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.O == InputData::PRESSED) {
		m_inputData.keyboardData.letters.O = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.O == InputData::RELEASED) {
		m_inputData.keyboardData.letters.O = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.P == InputData::PRESSED) {
		m_inputData.keyboardData.letters.P = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.P == InputData::RELEASED) {
		m_inputData.keyboardData.letters.P = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.Q == InputData::PRESSED) {
		m_inputData.keyboardData.letters.Q = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.Q == InputData::RELEASED) {
		m_inputData.keyboardData.letters.Q = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.R == InputData::PRESSED) {
		m_inputData.keyboardData.letters.R = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.R == InputData::RELEASED) {
		m_inputData.keyboardData.letters.R = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.S == InputData::PRESSED) {
		m_inputData.keyboardData.letters.S = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.S == InputData::RELEASED) {
		m_inputData.keyboardData.letters.S = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.T == InputData::PRESSED) {
		m_inputData.keyboardData.letters.T = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.T == InputData::RELEASED) {
		m_inputData.keyboardData.letters.T = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.U == InputData::PRESSED) {
		m_inputData.keyboardData.letters.U = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.U == InputData::RELEASED) {
		m_inputData.keyboardData.letters.U = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.V == InputData::PRESSED) {
		m_inputData.keyboardData.letters.V = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.V == InputData::RELEASED) {
		m_inputData.keyboardData.letters.V = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.W == InputData::PRESSED) {
		m_inputData.keyboardData.letters.W = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.W == InputData::RELEASED) {
		m_inputData.keyboardData.letters.W = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.X == InputData::PRESSED) {
		m_inputData.keyboardData.letters.X = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.X == InputData::RELEASED) {
		m_inputData.keyboardData.letters.X = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.Y == InputData::PRESSED) {
		m_inputData.keyboardData.letters.Y = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.Y == InputData::RELEASED) {
		m_inputData.keyboardData.letters.Y = InputData::DEFAULT;
	}

	if (m_inputData.keyboardData.letters.Z == InputData::PRESSED) {
		m_inputData.keyboardData.letters.Z = InputData::HELD;
	}
	else if (m_inputData.keyboardData.letters.Z == InputData::RELEASED) {
		m_inputData.keyboardData.letters.Z = InputData::DEFAULT;
	}

	//Mouse prep

	m_inputData.mouseData.MOVEMENT_X = 0;
	m_inputData.mouseData.MOVEMENT_Y = 0;

	if (m_inputData.mouseData.LEFT_CLICK == InputData::PRESSED) {
		m_inputData.mouseData.LEFT_CLICK = InputData::HELD;
	}
	else if (m_inputData.mouseData.LEFT_CLICK == InputData::RELEASED) {
		m_inputData.mouseData.LEFT_CLICK = InputData::DEFAULT;
	}

	if (m_inputData.mouseData.RIGHT_CLICK == InputData::PRESSED) {
		m_inputData.mouseData.RIGHT_CLICK = InputData::HELD;
	}
	else if (m_inputData.mouseData.RIGHT_CLICK == InputData::RELEASED) {
		m_inputData.mouseData.RIGHT_CLICK = InputData::DEFAULT;
	}

	if (m_inputData.mouseData.MIDDLE_CLICK == InputData::PRESSED) {
		m_inputData.mouseData.MIDDLE_CLICK = InputData::HELD;
	}
	else if (m_inputData.mouseData.MIDDLE_CLICK == InputData::RELEASED) {
		m_inputData.mouseData.MIDDLE_CLICK = InputData::DEFAULT;
	}
}

void StaticInput::_keyboardEvent(SDL_Event& e)
{
	InputData::KeyboardData& keyboard = StaticInput::m_inputData.keyboardData;

	if (e.key.keysym.sym == SDLK_a) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.A != InputData::HELD) {
			keyboard.letters.A = InputData::PRESSED;
		}
		else if(e.type == SDL_KEYUP) {
			keyboard.letters.A = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_b) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.B != InputData::HELD) {
			keyboard.letters.B = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.B = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_c) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.C != InputData::HELD) {
			keyboard.letters.C = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.C = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_d) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.D != InputData::HELD) {
			keyboard.letters.D = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.D = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_e) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.E != InputData::HELD) {
			keyboard.letters.E = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.E = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_f) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.F != InputData::HELD) {
			keyboard.letters.F = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.F = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_g) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.G != InputData::HELD) {
			keyboard.letters.G = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.G = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_h) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.H != InputData::HELD) {
			keyboard.letters.H = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.H = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_i) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.I != InputData::HELD) {
			keyboard.letters.I = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.I = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_j) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.J != InputData::HELD) {
			keyboard.letters.J = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.J = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_k) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.K != InputData::HELD) {
			keyboard.letters.K = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.K = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_l) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.L != InputData::HELD) {
			keyboard.letters.L = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.L = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_m) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.M != InputData::HELD) {
			keyboard.letters.M = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.M = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_n) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.N != InputData::HELD) {
			keyboard.letters.N = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.N = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_o) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.O != InputData::HELD) {
			keyboard.letters.O = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.O = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_p) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.P != InputData::HELD) {
			keyboard.letters.P = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.P = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_q) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.Q != InputData::HELD) {
			keyboard.letters.Q = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.Q = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_r) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.R != InputData::HELD) {
			keyboard.letters.R = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.R = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_s) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.S != InputData::HELD) {
			keyboard.letters.S = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.S = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_t) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.T != InputData::HELD) {
			keyboard.letters.T = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.T = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_u) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.U != InputData::HELD) {
			keyboard.letters.U = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.U = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_v) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.V != InputData::HELD) {
			keyboard.letters.V = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.V = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_w) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.W != InputData::HELD) {
			keyboard.letters.W = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.W = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_x) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.X != InputData::HELD) {
			keyboard.letters.X = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.X = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.sym == SDLK_y) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.Y != InputData::HELD) {
			keyboard.letters.Y = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.Y = InputData::RELEASED;
		}
	}
	else if (e.key.keysym.scancode == SDLK_z) {
		if (e.type == SDL_KEYDOWN && keyboard.letters.Z != InputData::HELD) {
			keyboard.letters.Z = InputData::PRESSED;
		}
		else if (e.type == SDL_KEYUP) {
			keyboard.letters.Z = InputData::RELEASED;
		}
	}
}

void StaticInput::_windowEvent(SDL_Event& e)
{
}

void StaticInput::_mouseEvent(SDL_Event& e)
{
	InputData::MouseData& mouseData = StaticInput::getMouseData();
	
	if (e.type == SDL_MOUSEMOTION) {
		mouseData.MOVEMENT_X = e.motion.xrel;
		mouseData.MOVEMENT_Y = e.motion.yrel;
		mouseData.CURRENT_X = e.motion.x;
		mouseData.CURRENT_Y = e.motion.y;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			mouseData.LEFT_CLICK = InputData::PRESSED;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			mouseData.RIGHT_CLICK = InputData::PRESSED;
		}
		else if (e.button.button == SDL_BUTTON_MIDDLE) {
			mouseData.MIDDLE_CLICK = InputData::PRESSED;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			mouseData.LEFT_CLICK = InputData::RELEASED;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			mouseData.RIGHT_CLICK = InputData::RELEASED;
		}
		else if (e.button.button == SDL_BUTTON_MIDDLE) {
			mouseData.MIDDLE_CLICK = InputData::RELEASED;
		}
	}
	else if (e.type == SDL_MOUSEWHEEL) {

	}
}
