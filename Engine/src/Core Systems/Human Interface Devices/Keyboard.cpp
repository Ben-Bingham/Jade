#include "Core Systems/Human Interface Devices/Keyboard.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	bool Keyboard::getKeyHeld(const Key key) const { //TODO does not seem to work
		return glfwGetKey(gWindow.getWindow(), keyToGLFW(key)) == stateToGLFW(KEY_REPEAT);
	}

	bool Keyboard::getKeyPressed(const Key key) const {
		return glfwGetKey(gWindow.getWindow(), keyToGLFW(key)) == stateToGLFW(KEY_PRESSED);
	}

	bool Keyboard::getKeyReleased(const Key key) const {
		return glfwGetKey(gWindow.getWindow(), keyToGLFW(key)) == stateToGLFW(KEY_RELEASED);
	}
}