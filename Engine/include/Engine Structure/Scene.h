#pragma once
#include <vector>
#include <memory>

#include "Entity Component System/Gameobjects/Gameobject.h"
#include "Entity Component System/Components/Rendering Components/PhongRenderingComponent.h"
#include "Entity Component System/Gameobjects/Lights/PointLight.h"
#include "Entity Component System/Gameobjects/Lights/DirectionalLight.h"
#include "High Level Rendering/MaterialCreator.h"
#include "Entity Component System/Components/Rendering Components/SolidRenderingComponent.h"
#include "High Level Rendering/Renderable Objects/SkyboxRenderableObject.h"

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

		void addLight(const PointLight& light) { m_Lights.push_back(std::make_shared<PointLight>(light)); };
		void addLight(const DirectionalLight& light) { m_Lights.push_back(std::make_shared<DirectionalLight>(light)); };

		std::vector<std::shared_ptr<Light>> getLights() { return m_Lights; }

		void begin();
		void update();
		std::vector<std::shared_ptr<RenderableObject>> getRenderableObjects(const Gameobject& gameobject);
		void cleanup();

		virtual void Begin() {}
		virtual void Update() {}
		virtual void Cleanup() {}

		void stop() { isRunning = false; }
		bool isRunning{ true };

	private:
		/*SkyboxRenderableObject initSkybox() {
			std::vector<std::string> imagePaths{
				"assets\\textures\\Sky skybox\\right.jpg",
				"assets\\textures\\Sky skybox\\left.jpg",
				"assets\\textures\\Sky skybox\\top.jpg",
				"assets\\textures\\Sky skybox\\bottom.jpg",
				"assets\\textures\\Sky skybox\\front.jpg",
				"assets\\textures\\Sky skybox\\back.jpg"
			};

			std::vector<Image> images;

			for (std::string imagePath : imagePaths) {
				images.push_back(Image(imagePath, false));
			}

			return SkyboxRenderableObject{ images };
		}

		SkyboxRenderableObject skybox;*/

		std::vector<std::shared_ptr<Gameobject>> m_Gameobjects;
		std::vector<std::shared_ptr<Light>> m_Lights;
	};
}