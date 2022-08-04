#include "Engine Structure/Subsystems/Keyboard.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void Keyboard::StartUp() {
		gWindow.setKeyCallback(keyCallback);
	}

	KeyState GLFWToState(int action) {
		switch (action) {
		default:
		case GLFW_PRESS: return KEY_PRESSED;
		case GLFW_RELEASE: return KEY_RELEASED;
		case GLFW_REPEAT: return KEY_REPEAT;
		}
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (key) {
		case GLFW_KEY_SPACE:			gKeyboard.KEY_SPACE = GLFWToState(action); break;
		case GLFW_KEY_APOSTROPHE:		gKeyboard.KEY_APOSTROPHE = GLFWToState(action); break;
		case GLFW_KEY_COMMA:			gKeyboard.KEY_COMMA = GLFWToState(action); break;
		case GLFW_KEY_MINUS:			gKeyboard.KEY_MINUS = GLFWToState(action); break;
		case GLFW_KEY_PERIOD:			gKeyboard.KEY_PERIOD = GLFWToState(action); break;
		case GLFW_KEY_SLASH:			gKeyboard.KEY_SLASH = GLFWToState(action); break;
		case GLFW_KEY_0:				gKeyboard.KEY_0 = GLFWToState(action); break;
		case GLFW_KEY_1:				gKeyboard.KEY_1 = GLFWToState(action); break;
		case GLFW_KEY_2:				gKeyboard.KEY_2 = GLFWToState(action); break;
		case GLFW_KEY_3:				gKeyboard.KEY_3 = GLFWToState(action); break;
		case GLFW_KEY_4:				gKeyboard.KEY_4 = GLFWToState(action); break;
		case GLFW_KEY_5:				gKeyboard.KEY_5 = GLFWToState(action); break;
		case GLFW_KEY_6:				gKeyboard.KEY_6 = GLFWToState(action); break;
		case GLFW_KEY_7:				gKeyboard.KEY_7 = GLFWToState(action); break;
		case GLFW_KEY_8:				gKeyboard.KEY_8 = GLFWToState(action); break;
		case GLFW_KEY_9:				gKeyboard.KEY_9 = GLFWToState(action); break;
		case GLFW_KEY_SEMICOLON:		gKeyboard.KEY_SEMICOLON = GLFWToState(action); break;
		case GLFW_KEY_EQUAL:			gKeyboard.KEY_EQUAL = GLFWToState(action); break;
		case GLFW_KEY_A:				gKeyboard.KEY_A = GLFWToState(action); break;
		case GLFW_KEY_B:				gKeyboard.KEY_B = GLFWToState(action); break;
		case GLFW_KEY_C:				gKeyboard.KEY_C = GLFWToState(action); break;
		case GLFW_KEY_D:				gKeyboard.KEY_D = GLFWToState(action); break;
		case GLFW_KEY_E:				gKeyboard.KEY_E = GLFWToState(action); break;
		case GLFW_KEY_F:				gKeyboard.KEY_F = GLFWToState(action); break;
		case GLFW_KEY_G:				gKeyboard.KEY_G = GLFWToState(action); break;
		case GLFW_KEY_H:				gKeyboard.KEY_H = GLFWToState(action); break;
		case GLFW_KEY_I:				gKeyboard.KEY_I = GLFWToState(action); break;
		case GLFW_KEY_J:				gKeyboard.KEY_J = GLFWToState(action); break;
		case GLFW_KEY_K:				gKeyboard.KEY_K = GLFWToState(action); break;
		case GLFW_KEY_L:				gKeyboard.KEY_L = GLFWToState(action); break;
		case GLFW_KEY_M:				gKeyboard.KEY_M = GLFWToState(action); break;
		case GLFW_KEY_N:				gKeyboard.KEY_N = GLFWToState(action); break;
		case GLFW_KEY_O:				gKeyboard.KEY_O = GLFWToState(action); break;
		case GLFW_KEY_P:				gKeyboard.KEY_P = GLFWToState(action); break;
		case GLFW_KEY_Q:				gKeyboard.KEY_Q = GLFWToState(action); break;
		case GLFW_KEY_R:				gKeyboard.KEY_R = GLFWToState(action); break;
		case GLFW_KEY_S:				gKeyboard.KEY_S = GLFWToState(action); break;
		case GLFW_KEY_T:				gKeyboard.KEY_T = GLFWToState(action); break;
		case GLFW_KEY_U:				gKeyboard.KEY_U = GLFWToState(action); break;
		case GLFW_KEY_V:				gKeyboard.KEY_V = GLFWToState(action); break;
		case GLFW_KEY_W:				gKeyboard.KEY_W = GLFWToState(action); break;
		case GLFW_KEY_X:				gKeyboard.KEY_X = GLFWToState(action); break;
		case GLFW_KEY_Y:				gKeyboard.KEY_Y = GLFWToState(action); break;
		case GLFW_KEY_Z:				gKeyboard.KEY_Z = GLFWToState(action); break;
		case GLFW_KEY_LEFT_BRACKET:		gKeyboard.KEY_LEFT_BRACKET = GLFWToState(action); break;
		case GLFW_KEY_BACKSLASH:		gKeyboard.KEY_BACKSLASH = GLFWToState(action); break;
		case GLFW_KEY_RIGHT_BRACKET:	gKeyboard.KEY_RIGHT_BRACKET = GLFWToState(action); break;
		case GLFW_KEY_GRAVE_ACCENT:		gKeyboard.KEY_GRAVE_ACCENT = GLFWToState(action); break;
		case GLFW_KEY_ESCAPE:			gKeyboard.KEY_ESCAPE = GLFWToState(action); break;
		case GLFW_KEY_ENTER:			gKeyboard.KEY_ENTER = GLFWToState(action); break;
		case GLFW_KEY_TAB:				gKeyboard.KEY_TAB = GLFWToState(action); break;
		case GLFW_KEY_BACKSPACE:		gKeyboard.KEY_BACKSPACE = GLFWToState(action); break;
		case GLFW_KEY_INSERT:			gKeyboard.KEY_INSERT = GLFWToState(action); break;
		case GLFW_KEY_DELETE:			gKeyboard.KEY_DELETE = GLFWToState(action); break;
		case GLFW_KEY_RIGHT:			gKeyboard.KEY_RIGHT = GLFWToState(action); break;
		case GLFW_KEY_LEFT:				gKeyboard.KEY_LEFT = GLFWToState(action); break;
		case GLFW_KEY_DOWN:				gKeyboard.KEY_DOWN = GLFWToState(action); break;
		case GLFW_KEY_UP:				gKeyboard.KEY_UP = GLFWToState(action); break;
		case GLFW_KEY_PAGE_UP:			gKeyboard.KEY_PAGE_UP = GLFWToState(action); break;
		case GLFW_KEY_PAGE_DOWN:		gKeyboard.KEY_PAGE_DOWN = GLFWToState(action); break;
		case GLFW_KEY_HOME:				gKeyboard.KEY_HOME = GLFWToState(action); break;
		case GLFW_KEY_END:				gKeyboard.KEY_END = GLFWToState(action); break;
		case GLFW_KEY_CAPS_LOCK:		gKeyboard.KEY_CAPS_LOCK = GLFWToState(action); break;
		case GLFW_KEY_SCROLL_LOCK:		gKeyboard.KEY_SCROLL_LOCK = GLFWToState(action); break;
		case GLFW_KEY_NUM_LOCK:			gKeyboard.KEY_NUM_LOCK = GLFWToState(action); break;
		case GLFW_KEY_PRINT_SCREEN:		gKeyboard.KEY_PRINT_SCREEN = GLFWToState(action); break;
		case GLFW_KEY_PAUSE:			gKeyboard.KEY_PAUSE = GLFWToState(action); break;
		case GLFW_KEY_F1:				gKeyboard.KEY_F1 = GLFWToState(action); break;
		case GLFW_KEY_F2:				gKeyboard.KEY_F2 = GLFWToState(action); break;
		case GLFW_KEY_F3:				gKeyboard.KEY_F3 = GLFWToState(action); break;
		case GLFW_KEY_F4:				gKeyboard.KEY_F4 = GLFWToState(action); break;
		case GLFW_KEY_F5:				gKeyboard.KEY_F5 = GLFWToState(action); break;
		case GLFW_KEY_F6:				gKeyboard.KEY_F6 = GLFWToState(action); break;
		case GLFW_KEY_F7:				gKeyboard.KEY_F7 = GLFWToState(action); break;
		case GLFW_KEY_F8:				gKeyboard.KEY_F8 = GLFWToState(action); break;
		case GLFW_KEY_F9:				gKeyboard.KEY_F9 = GLFWToState(action); break;
		case GLFW_KEY_F10:				gKeyboard.KEY_F10 = GLFWToState(action); break;
		case GLFW_KEY_F11:				gKeyboard.KEY_F11 = GLFWToState(action); break;
		case GLFW_KEY_F12:				gKeyboard.KEY_F12 = GLFWToState(action); break;
		case GLFW_KEY_KP_0:				gKeyboard.KEY_NUM_PAD_0 = GLFWToState(action); break;
		case GLFW_KEY_KP_1:				gKeyboard.KEY_NUM_PAD_1 = GLFWToState(action); break;
		case GLFW_KEY_KP_2:				gKeyboard.KEY_NUM_PAD_2 = GLFWToState(action); break;
		case GLFW_KEY_KP_3:				gKeyboard.KEY_NUM_PAD_3 = GLFWToState(action); break;
		case GLFW_KEY_KP_4:				gKeyboard.KEY_NUM_PAD_4 = GLFWToState(action); break;
		case GLFW_KEY_KP_5:				gKeyboard.KEY_NUM_PAD_5 = GLFWToState(action); break;
		case GLFW_KEY_KP_6:				gKeyboard.KEY_NUM_PAD_6 = GLFWToState(action); break;
		case GLFW_KEY_KP_7:				gKeyboard.KEY_NUM_PAD_7 = GLFWToState(action); break;
		case GLFW_KEY_KP_8:				gKeyboard.KEY_NUM_PAD_8 = GLFWToState(action); break;
		case GLFW_KEY_KP_9:				gKeyboard.KEY_NUM_PAD_9 = GLFWToState(action); break;
		case GLFW_KEY_KP_DECIMAL:		gKeyboard.KEY_NUM_PAD_DECIMAL = GLFWToState(action); break;
		case GLFW_KEY_KP_DIVIDE:		gKeyboard.KEY_NUM_PAD_DIVIDE = GLFWToState(action); break;
		case GLFW_KEY_KP_MULTIPLY:		gKeyboard.KEY_NUM_PAD_MULTIPLY = GLFWToState(action); break;
		case GLFW_KEY_KP_SUBTRACT:		gKeyboard.KEY_NUM_PAD_SUBTRACT = GLFWToState(action); break;
		case GLFW_KEY_KP_ADD:			gKeyboard.KEY_NUM_PAD_ADD = GLFWToState(action); break;
		case GLFW_KEY_KP_ENTER:			gKeyboard.KEY_NUM_PAD_ENTER = GLFWToState(action); break;
		case GLFW_KEY_KP_EQUAL:			gKeyboard.KEY_NUM_PAD_EQUAL = GLFWToState(action); break;
		case GLFW_KEY_LEFT_SHIFT:		gKeyboard.KEY_LEFT_SHIFT = GLFWToState(action); break;
		case GLFW_KEY_LEFT_CONTROL:		gKeyboard.KEY_LEFT_CONTROL = GLFWToState(action); break;
		case GLFW_KEY_LEFT_ALT:			gKeyboard.KEY_LEFT_ALT = GLFWToState(action); break;
		case GLFW_KEY_RIGHT_SHIFT:		gKeyboard.KEY_RIGHT_SHIFT = GLFWToState(action); break;
		case GLFW_KEY_RIGHT_CONTROL:	gKeyboard.KEY_RIGHT_CONTROL = GLFWToState(action); break;
		case GLFW_KEY_RIGHT_ALT:		gKeyboard.KEY_RIGHT_ALT = GLFWToState(action); break;
		default:
		case GLFW_KEY_UNKNOWN:			gKeyboard.KEY_UNKNOWN = GLFWToState(action); break;
		}
	}
}