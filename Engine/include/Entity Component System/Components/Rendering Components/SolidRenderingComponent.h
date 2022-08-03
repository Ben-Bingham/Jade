#pragma once
#include "Entity Component System/Components/Rendering Components/RenderComponent.h"
#include "High Level Rendering/PShaders/SolidShader.h"

namespace Jade {
	class SolidRenderingComponent : public RenderComponent {
	public:
		SolidRenderingComponent(Shape shape, Colour colour);

		void Begin() override {

			Transform* transform = getGameobject().getComponent<Transform>(); //TODO
			for (std::shared_ptr<RenderableObject> renderable : renderables) {
				renderable->setTransform(transform);
				renderable->calculateModelMatrix();
			}
		}
	};
}