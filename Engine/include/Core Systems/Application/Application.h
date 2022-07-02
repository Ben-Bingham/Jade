#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Low Level Rendering/Window.h"
#include "Low Level Rendering/GLEW.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Core Systems/Game Objects System/Scene.h"
#include "Low Level Rendering/Shaders/ShaderHeader.h"


#include "Jade.h"

namespace Jade {
	class Application {
	public:
		float DELTA_TIME = 0;
		unsigned int SCREEN_WIDTH = 400;
		unsigned int SCREEN_HEIGHT = 200;
		bool GAME_OPEN = true;

		Application(std::string windowName = "Jade") : m_Window(SCREEN_WIDTH, SCREEN_HEIGHT, windowName), m_LastFrameTime(0) {}

		void Begin() {			
			GLEW glew = GLEW();
			glEnable(GL_DEPTH_TEST); //TODO

			// Uncomment for wireframe rendering //todo
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //todo

			VertexShader vertexShader(TextFile("assets\\shaders\\default.vert"));

			FragmentShader fragmentShader(TextFile("assets\\shaders\\default.frag"));

			m_ShaderProgram = std::make_unique<ShaderProgram>(fragmentShader, vertexShader);

			glCheckError();
		}

		void Update() {
			// Pre Render
			GAME_OPEN = !m_Window.getWindowShouldClose();
			m_Window.pollEvents();
			
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //TODO
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //TODO
			
			// Render
			m_ShaderProgram->use();
			// Upload View and Projection //TODO
			
			m_ActiveScene->render(*m_ShaderProgram);
			
			// Post Render
		}

		void LateUpdate() {
			m_Window.swapBuffers();
			glCheckError();
		}

		void Cleanup() {
			m_Window.dispose();
		}

		void setActiveScene(const Jade::Scene& scene) { m_ActiveScene = std::make_unique<Jade::Scene>(scene); }

	private:
		float m_LastFrameTime;
		Jade::Window m_Window;
		std::unique_ptr<Jade::Scene> m_ActiveScene;
		std::unique_ptr<Jade::ShaderProgram> m_ShaderProgram;
	};
}