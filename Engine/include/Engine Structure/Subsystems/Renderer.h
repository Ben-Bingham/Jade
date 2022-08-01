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
		Renderer()
			: m_View(glm::mat4(1.0f)), m_Projection(glm::mat4(1.0f)) {}

		void StartUp() override {
			addShader(PhongShader());

			addShader(SolidShader());
		}

		void ShutDown() override {
			for (std::vector<std::shared_ptr<RenderableObject>> renderableVector : m_Renderables) {
				for (std::shared_ptr<RenderableObject> renderable : renderableVector) {
					renderable->dispose();
				}
			}

			for (std::shared_ptr<PShader> shader : m_PShaders) {
				shader->dispose();
			}
		}

		void loadScene(std::shared_ptr<Scene> scene);

		void update();

		void addRenderable(std::shared_ptr<RenderableObject> renderable);

		void render();

		void setMatrices(const glm::mat4& view, const glm::mat4& projection);

		void addShader(const PhongShader& shader) {
			for (std::shared_ptr<PShader> rSet : m_PShaders) {
				if (rSet->ruleSet == shader.ruleSet) {
					LOG("There is alread a ruleset of that type attached to the renderer, the one you added probably wont be used", WARNING);
					break;
				}
			}
			m_PShaders.push_back(std::make_shared<PhongShader>(shader));
			m_Renderables.resize(m_PShaders.size());
		}

		void addShader(const SolidShader& shader) {
			for (std::shared_ptr<PShader> rSet : m_PShaders) {
				if (rSet->ruleSet == shader.ruleSet) {
					LOG("There is alread a ruleset of that type attached to the renderer, the one you added probably wont be used", WARNING);
					break;
				}
			}
			m_PShaders.push_back(std::make_shared<SolidShader>(shader));
			m_Renderables.resize(m_PShaders.size());
		}

	private:
		std::vector<std::shared_ptr<PShader>> m_PShaders;
		std::vector<std::vector<std::shared_ptr<RenderableObject>>> m_Renderables;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}