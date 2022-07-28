#pragma once
#include <GLFW/glfw3.h>

#include "Engine Structure/Subsystems/Subsystem.h"

namespace Jade {
	enum MouseButton {
		BUTTON_1,
		BUTTON_2,
		BUTTON_3,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_MIDDLE
	};

	enum MouseButtonState {
		BUTTON_RELEASED, BUTTON_PRESSED
	};
 
	class Mouse : public Subsystem {
	public:
		Mouse() : 
			m_Button1(BUTTON_RELEASED),
			m_Button2(BUTTON_RELEASED),
			m_Button3(BUTTON_RELEASED),
			m_XPosition(0),
			m_YPosition(0),
			m_ScrollOffset(1)
		{}

		void StartUp() override {

		}

		void ShutDown() override {

		}

		bool getButtonPressed(MouseButton button) {
			switch (button) {
			default:
			case BUTTON_LEFT:
			case BUTTON_1: return m_Button1 == BUTTON_PRESSED;
			case BUTTON_RIGHT:
			case BUTTON_2: return m_Button2 == BUTTON_PRESSED;
			case BUTTON_MIDDLE:
			case BUTTON_3: return m_Button3 == BUTTON_PRESSED;
			}
		}

		bool getButtonReleased(MouseButton button) {
			switch (button) {
			default:
			case BUTTON_LEFT:
			case BUTTON_1: return m_Button1 == BUTTON_RELEASED;
			case BUTTON_RIGHT:
			case BUTTON_2: return m_Button2 == BUTTON_RELEASED;
			case BUTTON_MIDDLE:
			case BUTTON_3: return m_Button3 == BUTTON_RELEASED;
			}
		}

		void setButton(MouseButton button, MouseButtonState state) {
			switch (button) {
			default:
			case BUTTON_LEFT:
			case BUTTON_1: m_Button1 = state; break;
			case BUTTON_RIGHT:
			case BUTTON_2: m_Button2 = state; break;
			case BUTTON_MIDDLE:
			case BUTTON_3: m_Button3 = state; break;
			}
		}

		void setPosition(unsigned int xPos, unsigned int yPos) {
			m_XPosition = xPos;
			m_YPosition = yPos;
		}

		void setScrollOffset(int offset) {
			m_ScrollOffset = offset;
		}

		int getXPosition() { return m_XPosition; }
		int getYPosition() { return m_YPosition; }
		int getScrollOffset() { return m_ScrollOffset; }

		static MouseButton intToMouseButton(int button) {
			switch (button) {
			default:
			case GLFW_MOUSE_BUTTON_1: return BUTTON_1;
			case GLFW_MOUSE_BUTTON_2: return BUTTON_2;
			case GLFW_MOUSE_BUTTON_3: return BUTTON_3;
			}
		}

		static MouseButtonState intToMouseState(int state) {
			switch (state) {
			default:
			case GLFW_PRESS: return BUTTON_PRESSED;
			case GLFW_RELEASE: return BUTTON_RELEASED;
			}
		}

	private:
		// Top left of screen is (0,0) bottom right is the screen size in pixels
		int m_XPosition;
		int m_YPosition;

		int m_ScrollOffset;

		MouseButtonState m_Button1;
		MouseButtonState m_Button2;
		MouseButtonState m_Button3;
	};
}