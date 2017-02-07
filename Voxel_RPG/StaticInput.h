#pragma once
#include "SDL\SDL.h"

struct InputData{
	enum KeyState {
		DEFAULT,PRESSED,HELD,RELEASED
	};
	
	struct KeyboardData {
		struct Letters {
			KeyState A;
			KeyState B;
			KeyState C;
			KeyState D;
			KeyState E;
			KeyState F;
			KeyState G;
			KeyState H;
			KeyState I;
			KeyState J;
			KeyState K;
			KeyState L;
			KeyState M;
			KeyState N;
			KeyState O;
			KeyState P;
			KeyState Q;
			KeyState R;
			KeyState S;
			KeyState T;
			KeyState U;
			KeyState V;
			KeyState W;
			KeyState X;
			KeyState Y;
			KeyState Z;
		} letters;
		struct Symbols {

		} symbols;
		struct Numbers {

	} numbers;
		struct Modifiers {
			short CAPS_LOCK;
			short NUM_LOCK;
			short LEFT_SHIFT;
			short RIGHT_SHIFT;
			short TAB;
			short ENTER;
			short LEFT_CTRL;
			short RIGHT_CTRL;
			short LEFT_ALT;
			short RIGHT_ALT;
			short BACK_SPACE;
		} modifiers;
	} keyboardData;

	struct MouseData {
		KeyState LEFT_CLICK;
		KeyState RIGHT_CLICK;
		KeyState MIDDLE_CLICK;
		short SCROLLING;
		short SCROLL_SPEED;
		int CURRENT_X;
		int CURRENT_Y;
		int MOVEMENT_X;
		int MOVEMENT_Y;
	} mouseData;
};

class StaticInput {
public:
	static void update();
	static InputData::KeyboardData& getKeyboardData();
	static InputData::MouseData& getMouseData();

private:
	static InputData m_inputData;

	static void _prepInput();
	static void _keyboardEvent(SDL_Event& e);
	static void _windowEvent(SDL_Event& e);
	static void _mouseEvent(SDL_Event& e);
protected:
};