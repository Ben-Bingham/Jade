#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"
#include "Core Systems/Logging/OpenGLErrors.h"
#include "Engine Structure/Subsystems/Subsystem.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/PShaders/SolidShader.h"
#include "Engine Structure/Scene.h"
#include "Entity Component System/Gameobjects/Lights/PointLight.h"

namespace Jade {
	class Engine;

	class Renderer : public Subsystem {
	public:
		Renderer() {}

		void StartUp() override {}

		void ShutDown() override {}

		void update() {
			glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};
}