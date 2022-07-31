#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Entity Component System/Components/Component.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
	class RenderComponent : public Component {
	public:
		virtual ~RenderComponent() = 0;

		std::vector<RenderableObject*> renderables;
	};
}