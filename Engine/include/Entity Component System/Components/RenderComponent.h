#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Entity Component System/Component.h"
#include <High Level Rendering/Renderable Objects/RenderableObject.h>

namespace Jade {
	class RenderComponent : public Component {
	public:
		virtual ~RenderComponent() = 0;

		void translate(glm::vec3 vector) {
			for (RenderableObject* renderable : renderables) {
				renderable->getTransform().position.x += vector.x;
				renderable->getTransform().position.y += vector.y;
				renderable->getTransform().position.z += vector.z;
			}
		}

		std::vector<RenderableObject*> renderables;
	};
}