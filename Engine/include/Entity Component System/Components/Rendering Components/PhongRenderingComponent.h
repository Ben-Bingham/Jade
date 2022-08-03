#pragma once
#include "Entity Component System/Components/Rendering Components/RenderComponent.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	class Application;

	class PhongRenderingComponent : public RenderComponent {
	public:
		PhongRenderingComponent(Model& model);
		PhongRenderingComponent(Shape shape, const Material& material);

		void Begin() override {
			Transform* transform = getGameobject().getComponent<Transform>();
			for (std::shared_ptr<RenderableObject> renderable : renderables) {
				renderable->setTransform(transform);
				renderable->calculateModelMatrix();
			}
		}

	private:
		std::vector<std::shared_ptr<Material>> m_Materials;
	};
}