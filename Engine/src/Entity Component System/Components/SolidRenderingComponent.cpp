#include "Entity Component System/Components/Rendering Components/SolidRenderingComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	SolidRenderingComponent::SolidRenderingComponent(Shape shape, Colour colour) {
		renderables.push_back(std::make_shared<SolidRenderable>(colour, shape));
	}
}