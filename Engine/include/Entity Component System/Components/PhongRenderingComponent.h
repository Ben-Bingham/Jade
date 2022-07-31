#pragma once
#include "Component.h"
#include "Entity Component System/Components/RenderComponent.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	class Application;

	class PhongRenderingComponent : public RenderComponent { //TODO the name sucks
	public:
		PhongRenderingComponent(Model* model);

		void Begin() override {
			Transform* transform = getGameobject()->getComponent<Transform>();
			for (RenderableObject* renderable : renderables) {
				renderable->setTransform(transform);
			}
		}

	private:
		std::vector<Material> m_Materials;
	};
}