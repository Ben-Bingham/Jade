#include <glm/glm.hpp>

#include "Jade.h"

#include "Engine Structure/Application.h"

namespace Jade {
	Window WINDOW(640, 480, "", false); //TODO make a getter that creates one than always returns the same one
	Keyboard KEYBOARD(&WINDOW);
	Mouse MOUSE;
	Camera CAMERA(45.0f);

	void Application::begin() {
		Begin();

		WINDOW.setMouseButtonCallback(mouseButtonCallback);
		WINDOW.setMousePositionCallback(mousePositionCallback);
		WINDOW.setScrollWheelCallback(mouseScrolWheelCallback);
		WINDOW.setFrameBufferSizeCallback(windowSizeCallBack);

		// Open GL Settings
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);

		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			LOG("OpenGL debug context available", Jade::INFO);
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glCheckError();

		m_ActiveScene->begin(*this);
	}

	void Application::update() {
		Update();

		WINDOW.pollEvents();

		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CAMERA.updateCameraVectors();

		glm::mat4 view;
		view = CAMERA.getViewMatrix();

		WINDOW.calculateProjectionMatrix(CAMERA.getFOV());

		m_Renderer.setMatrices(view, WINDOW.getProjectionMatrix());
		m_Renderer.render(CAMERA.getTransform().position);

		m_ActiveScene->update();
	}

	void Application::lateUpdate() {
		LateUpdate();
		
		WINDOW.swapBuffers();
		glCheckError();
	}

	void Application::cleanup() {
		Cleanup();

		m_Renderer.dispose();
		WINDOW.dispose();

		m_ActiveScene->cleanup();
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		MOUSE.setButton(Mouse::intToMouseButton(button), Mouse::intToMouseState(action));
	}

	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
		MOUSE.setPosition((unsigned int)xpos, (unsigned int)ypos);
	}

	void mouseScrolWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
		MOUSE.setScrollOffset((int)yoffset);
	}

	void windowSizeCallBack(GLFWwindow* window, int width, int height) {
		WINDOW.setWidth((unsigned int)width);
		WINDOW.setHeight((unsigned int)height);

		WINDOW.calculateProjectionMatrix(CAMERA.getFOV());

		glViewport(0, 0, WINDOW.getWidth(), WINDOW.getHeight());
	}

	void APIENTRY glDebugOutput(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* userParam) {
		Jade::LogLevel level;
		switch (severity) {
		default:
		case GL_DEBUG_SEVERITY_HIGH:			level = Jade::ERROR; break;
		case GL_DEBUG_SEVERITY_MEDIUM:			level = Jade::WARNING; break;
		case GL_DEBUG_SEVERITY_LOW:				level = Jade::WARNING; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	level = Jade::INFO; break;
		}

		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
		LOG("---------------", level);

		std::string string = "Debug message (";
		string += std::to_string(id);
		string += "): ";
		string += message;

		LOG(string, level);

		string = "";
		switch (source) {
		case GL_DEBUG_SOURCE_API:             string += "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   string += "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: string += "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     string += "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     string += "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           string += "Source: Other"; break;
		}
		LOG(string, level);

		string = "";
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:               string += "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: string += "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  string += "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         string += "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         string += "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              string += "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          string += "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           string += "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               string += "Type: Other"; break;
		}
		LOG(string, level);
		string = "";
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:         string += "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       string += "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          string += "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: string += "Severity: notification"; break;
		}
		LOG(string, level);
		LOG("---------------", level);
	}
}