#pragma once
#include "Entity Component System/Components/Rendering Components/RenderComponent.h"
#include "High Level Rendering/PShaders/SolidShader.h"

namespace Jade {
	class SolidRenderingComponent : public RenderComponent {
	public:
		SolidRenderingComponent(Shape shape, Colour colour);
	};
}