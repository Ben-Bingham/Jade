#include "Entity Component System/Components/Rendering Components/SolidRenderingComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	SolidRenderingComponent::SolidRenderingComponent(Shape shape, Colour colour) {
		shader = std::make_shared<SolidShader>();

		renderables.push_back(std::make_shared<SolidRenderable>(colour, shape));
	}
}