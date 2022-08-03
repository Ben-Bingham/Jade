#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Entity Component System/Components/Component.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
	class RenderComponent : public Component {
	public:
		virtual ~RenderComponent() = 0;

		void render();

		virtual void Render() {}

		std::vector<std::shared_ptr<RenderableObject>> renderables;
		std::shared_ptr<PShader> shader;

	private:
	};
}