#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade{
	enum Key {
		KEY_SPACE,
		KEY_APOSTROPHE,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON,
		KEY_EQUAL,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LEFT_BRACKET,
		KEY_BACKSLASH,
		KEY_RIGHT_BRACKET,
		KEY_GRAVE_ACCENT,
		KEY_ESCAPE,
		KEY_ENTER,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_INSERT,
		KEY_DELETE,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_CAPS_LOCK,
		KEY_SCROLL_LOCK,
		KEY_NUM_LOCK,
		KEY_PRINT_SCREEN,
		KEY_PAUSE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_NUM_PAD_0,
		KEY_NUM_PAD_1,
		KEY_NUM_PAD_2,
		KEY_NUM_PAD_3,
		KEY_NUM_PAD_4,
		KEY_NUM_PAD_5,
		KEY_NUM_PAD_6,
		KEY_NUM_PAD_7,
		KEY_NUM_PAD_8,
		KEY_NUM_PAD_9,
		KEY_NUM_PAD_DECIMAL,
		KEY_NUM_PAD_DIVIDE,
		KEY_NUM_PAD_MULTIPLY,
		KEY_NUM_PAD_SUBTRACT,
		KEY_NUM_PAD_ADD,
		KEY_NUM_PAD_ENTER,
		KEY_NUM_PAD_EQUAL,
		KEY_LEFT_SHIFT,
		KEY_LEFT_CONTROL,
		KEY_LEFT_ALT,
		KEY_RIGHT_SHIFT,
		KEY_RIGHT_CONTROL,
		KEY_RIGHT_ALT,
	};

	enum KeyState {
		KEY_PRESSED, KEY_RELEASED, KEY_REPEAT
	};

	class Keyboard : public Subsystem {
	public:
		Keyboard() {}

		void StartUp() override {}
		void ShutDown() override {}

		bool getKeyPressed(const Key key) const;
		bool getKeyReleased(const Key key) const;
		bool getKeyHeld(const Key key) const; //TODO broken

	private:
		int keyToGLFW(const Key key) const {
			switch (key) {
			default:
			case KEY_SPACE:					return GLFW_KEY_SPACE;
			case KEY_APOSTROPHE:			return GLFW_KEY_APOSTROPHE;
			case KEY_COMMA:					return GLFW_KEY_COMMA;
			case KEY_MINUS:					return GLFW_KEY_MINUS;
			case KEY_PERIOD:				return GLFW_KEY_PERIOD;
			case KEY_SLASH:					return GLFW_KEY_SLASH;
			case KEY_0:						return GLFW_KEY_0;
			case KEY_1:						return GLFW_KEY_1;
			case KEY_2:						return GLFW_KEY_2;
			case KEY_3:						return GLFW_KEY_3;
			case KEY_4:						return GLFW_KEY_4;
			case KEY_5:						return GLFW_KEY_5;
			case KEY_6:						return GLFW_KEY_6;
			case KEY_7:						return GLFW_KEY_7;
			case KEY_8:						return GLFW_KEY_8;
			case KEY_9:						return GLFW_KEY_9;
			case KEY_SEMICOLON:				return GLFW_KEY_SEMICOLON;
			case KEY_EQUAL:					return GLFW_KEY_EQUAL;
			case KEY_A:						return GLFW_KEY_A;
			case KEY_B:						return GLFW_KEY_B;
			case KEY_C:						return GLFW_KEY_C;
			case KEY_D:						return GLFW_KEY_D;
			case KEY_E:						return GLFW_KEY_E;
			case KEY_F:						return GLFW_KEY_F;
			case KEY_G:						return GLFW_KEY_G;
			case KEY_H:						return GLFW_KEY_H;
			case KEY_I:						return GLFW_KEY_I;
			case KEY_J:						return GLFW_KEY_J;
			case KEY_K:						return GLFW_KEY_K;
			case KEY_L:						return GLFW_KEY_L;
			case KEY_M:						return GLFW_KEY_M;
			case KEY_N:						return GLFW_KEY_N;
			case KEY_O:						return GLFW_KEY_O;
			case KEY_P:						return GLFW_KEY_P;
			case KEY_Q:						return GLFW_KEY_Q;
			case KEY_R:						return GLFW_KEY_R;
			case KEY_S:						return GLFW_KEY_S;
			case KEY_T:						return GLFW_KEY_T;
			case KEY_U:						return GLFW_KEY_U;
			case KEY_V:						return GLFW_KEY_V;
			case KEY_W:						return GLFW_KEY_W;
			case KEY_X:						return GLFW_KEY_X;
			case KEY_Y:						return GLFW_KEY_Y;
			case KEY_Z:						return GLFW_KEY_Z;
			case KEY_LEFT_BRACKET:			return GLFW_KEY_LEFT_BRACKET;
			case KEY_BACKSLASH:				return GLFW_KEY_BACKSLASH;
			case KEY_RIGHT_BRACKET:			return GLFW_KEY_RIGHT_BRACKET;
			case KEY_GRAVE_ACCENT:			return GLFW_KEY_GRAVE_ACCENT;
			case KEY_ESCAPE:				return GLFW_KEY_ESCAPE;
			case KEY_ENTER:					return GLFW_KEY_ENTER;
			case KEY_TAB:					return GLFW_KEY_TAB;
			case KEY_BACKSPACE:				return GLFW_KEY_BACKSPACE;
			case KEY_INSERT:				return GLFW_KEY_INSERT;
			case KEY_DELETE:				return GLFW_KEY_DELETE;
			case KEY_RIGHT:					return GLFW_KEY_RIGHT;
			case KEY_LEFT:					return GLFW_KEY_LEFT;
			case KEY_DOWN:					return GLFW_KEY_DOWN;
			case KEY_UP:					return GLFW_KEY_UP;
			case KEY_PAGE_UP:				return GLFW_KEY_PAGE_UP;
			case KEY_PAGE_DOWN:				return GLFW_KEY_PAGE_DOWN;
			case KEY_HOME:					return GLFW_KEY_HOME;
			case KEY_END:					return GLFW_KEY_END;
			case KEY_CAPS_LOCK:				return GLFW_KEY_CAPS_LOCK;
			case KEY_SCROLL_LOCK:			return GLFW_KEY_SCROLL_LOCK;
			case KEY_NUM_LOCK:				return GLFW_KEY_NUM_LOCK;
			case KEY_PRINT_SCREEN:			return GLFW_KEY_PRINT_SCREEN;
			case KEY_PAUSE:					return GLFW_KEY_PAUSE;
			case KEY_F1:					return GLFW_KEY_F1;
			case KEY_F2:					return GLFW_KEY_F2;
			case KEY_F3:					return GLFW_KEY_F3;
			case KEY_F4:					return GLFW_KEY_F4;
			case KEY_F5:					return GLFW_KEY_F5;
			case KEY_F6:					return GLFW_KEY_F6;
			case KEY_F7:					return GLFW_KEY_F7;
			case KEY_F8:					return GLFW_KEY_F8;
			case KEY_F9:					return GLFW_KEY_F9;
			case KEY_F10:					return GLFW_KEY_F10;
			case KEY_F11:					return GLFW_KEY_F11;
			case KEY_F12:					return GLFW_KEY_F12;
			case KEY_NUM_PAD_0:				return GLFW_KEY_KP_0;
			case KEY_NUM_PAD_1:				return GLFW_KEY_KP_1;
			case KEY_NUM_PAD_2:				return GLFW_KEY_KP_2;
			case KEY_NUM_PAD_3:				return GLFW_KEY_KP_3;
			case KEY_NUM_PAD_4:				return GLFW_KEY_KP_4;
			case KEY_NUM_PAD_5:				return GLFW_KEY_KP_5;
			case KEY_NUM_PAD_6:				return GLFW_KEY_KP_6;
			case KEY_NUM_PAD_7:				return GLFW_KEY_KP_7;
			case KEY_NUM_PAD_8:				return GLFW_KEY_KP_8;
			case KEY_NUM_PAD_9:				return GLFW_KEY_KP_9;
			case KEY_NUM_PAD_DECIMAL:		return GLFW_KEY_KP_DECIMAL;
			case KEY_NUM_PAD_DIVIDE:		return GLFW_KEY_KP_DIVIDE;
			case KEY_NUM_PAD_MULTIPLY:		return GLFW_KEY_KP_MULTIPLY;
			case KEY_NUM_PAD_SUBTRACT:		return GLFW_KEY_KP_SUBTRACT;
			case KEY_NUM_PAD_ADD:			return GLFW_KEY_KP_ADD;
			case KEY_NUM_PAD_ENTER:			return GLFW_KEY_KP_ENTER;
			case KEY_NUM_PAD_EQUAL:			return GLFW_KEY_KP_EQUAL;
			case KEY_LEFT_SHIFT:			return GLFW_KEY_LEFT_SHIFT;
			case KEY_LEFT_CONTROL:			return GLFW_KEY_LEFT_CONTROL;
			case KEY_LEFT_ALT:				return GLFW_KEY_LEFT_ALT;
			case KEY_RIGHT_SHIFT:			return GLFW_KEY_RIGHT_SHIFT;
			case KEY_RIGHT_CONTROL:			return GLFW_KEY_RIGHT_CONTROL;
			case KEY_RIGHT_ALT:				return GLFW_KEY_RIGHT_ALT;
			}
		}

		int stateToGLFW(const KeyState state) const {
			switch (state) {
			default:
			case KEY_PRESSED:    return GLFW_PRESS;
			case KEY_RELEASED:   return GLFW_RELEASE;
			case KEY_REPEAT:     return GLFW_REPEAT;
			}
		}
	};
}