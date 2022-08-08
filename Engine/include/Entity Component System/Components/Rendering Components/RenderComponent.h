#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Entity Component System/Components/Component.h"
#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
	class RenderComponent : public Component {
	public:
		RenderComponent() {}

		virtual ~RenderComponent() = 0;

		void Begin() override {
			m_Transform = std::shared_ptr<Transform>(getGameobject().getComponent<Transform>());
			BeginRenderComponent();
		}

		virtual void BeginRenderComponent() {}

		void render(std::shared_ptr<PShader> shader); //TODO rmove maybe?
		void render(); // TODO remove maybe?
		void render(ShaderProgram program); //TODO remove maybe?

		virtual void Render() {}
		virtual void Render(ShaderProgram program) {}

		std::vector<std::shared_ptr<RenderableObject>> renderables;
		std::shared_ptr<PShader> shader;

	private:
		glm::mat4 m_ModelMatrix{ 1.0f };
		std::shared_ptr<Transform> m_Transform{ nullptr };

		void calculateModelMatrix() {
			m_ModelMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::mat4_cast(m_Transform->rotation);
			m_ModelMatrix = glm::translate(m_ModelMatrix, m_Transform->position);
			m_ModelMatrix = glm::scale(m_ModelMatrix, m_Transform->scale);
		}
	};
}