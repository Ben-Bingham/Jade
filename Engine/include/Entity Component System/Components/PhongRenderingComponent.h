#pragma once
#include "Component.h"
#include "Entity Component System/Components/RenderComponent.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	class Application;

	class PhongRenderingComponent : public RenderComponent {
	public:
		PhongRenderingComponent(Model* model);

		void Begin() override {
			Transform* transform = getGameobject().getComponent<Transform>();
			for (std::shared_ptr<RenderableObject> renderable : renderables) {
				renderable->setTransform(transform);
				renderable->calculateModelMatrix();
			}
		}

	private:
		std::vector<Material> m_Materials;
	};
}