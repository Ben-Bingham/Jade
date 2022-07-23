#pragma once
#include <GLFW/glfw3.h>

namespace Jade {
	enum Key {
		KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_LEFT_SHIFT, KEY_ESCAPE //TODO add all keys
	};

	enum KeyState {
		KEY_PRESSED, KEY_RELEASED, KEY_REPEAT
	};

	class Keyboard {
	public:
		Keyboard(Window* window) : m_Window(window) {}

		bool getKeyPressed(const Key key) const {
			return glfwGetKey(m_Window->getWindow(), keyToGLFW(key)) == stateToGLFW(KEY_PRESSED);
		}

		bool getKeyReleased(const Key key) const {
			return glfwGetKey(m_Window->getWindow(), keyToGLFW(key)) == stateToGLFW(KEY_RELEASED);
		}

		bool getKeyHeld(const Key key) const { //TODO does not seem to work
			return glfwGetKey(m_Window->getWindow(), keyToGLFW(key)) == stateToGLFW(KEY_REPEAT);
		}

	private:
		Window* m_Window;

		int keyToGLFW(const Key key) const {
			switch (key) {
			default:
			case KEY_W:             return GLFW_KEY_W;
			case KEY_A:             return GLFW_KEY_A;
			case KEY_S:             return GLFW_KEY_S;
			case KEY_D:             return GLFW_KEY_D;
			case KEY_SPACE:         return GLFW_KEY_SPACE;
			case KEY_LEFT_SHIFT:    return GLFW_KEY_LEFT_SHIFT;
			case KEY_ESCAPE:		return GLFW_KEY_ESCAPE;
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