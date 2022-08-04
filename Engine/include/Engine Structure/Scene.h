#pragma once
#include <vector>
#include <memory>

#include "Entity Component System/Gameobjects/Gameobject.h"
#include "Entity Component System/Components/Rendering Components/PhongRenderingComponent.h"
#include "Entity Component System/Gameobjects/Lights/PointLight.h"
#include "Entity Component System/Gameobjects/Lights/DirectionalLight.h"
#include "High Level Rendering/MaterialCreator.h"
#include "Entity Component System/Components/Rendering Components/SolidRenderingComponent.h"

namespace Jade {
	class Application;

	class Scene {
	public:
		Scene() {}
		Scene(const Scene&) = default;
		Scene(Scene&&) = default;
		Scene& operator=(const Scene&) = default;
		Scene& operator=(Scene&&) = default;
		virtual ~Scene() = 0;

		void addGameobject(const Gameobject& gameobject) { m_Gameobjects.push_back(std::make_shared<Gameobject>(gameobject)); }
		void addGameobject(const PointLight& light) { addLight(light); }
		void addGameobject(const DirectionalLight& light) { addLight(light); }

		void addLight(const PointLight& light) { 
			m_Lights.push_back(std::make_shared<PointLight>(light));
			for (std::shared_ptr<Gameobject> gb : m_Gameobjects) {
				RenderComponent* renderComp = gb->getComponent<RenderComponent>();
				if (renderComp != nullptr) {
					renderComp->shader->addPointLight(light);
				}
			}
		};

		void addLight(const DirectionalLight& light) { 
			m_Lights.push_back(std::make_shared<DirectionalLight>(light));
			for (std::shared_ptr<Gameobject> gb : m_Gameobjects) {
				RenderComponent* renderComp = gb->getComponent<RenderComponent>();
				if (renderComp != nullptr) {
					renderComp->shader->addDirectionalLight(light);
				}
			}
		};

		std::vector<std::shared_ptr<Light>> getLights() { return m_Lights; }

		void begin();
		void update();
		void cleanup();

		virtual void Begin() {}
		virtual void Update() {}
		virtual void Cleanup() {}

		void render(const std::shared_ptr<Gameobject> gb) {
			RenderComponent* renderComp = gb->getComponent<RenderComponent>();
			if (renderComp != nullptr) {
				renderComp->render();
			}
		}

		void stop() {
			isRunning = false;
		}

		bool isRunning{true};

	private:
		std::vector<std::shared_ptr<Gameobject>> m_Gameobjects;
		std::vector<std::shared_ptr<Light>> m_Lights;
	};
}