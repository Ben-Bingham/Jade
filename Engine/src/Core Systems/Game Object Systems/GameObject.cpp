#include <memory>

#include "Jade.h"

#include "Core Systems/Game Objects System/GameObject.h"
#include "Low Level Rendering/Shaders/ShaderProgram.h"
#include "Core Systems/Components/Transform.h"
#include "Core Systems/Components/Renderer.h"

namespace Jade {
	GameObject::GameObject() : m_ID(getNextID()) {
		renderer = new CubeRenderer(*this);
		transform = new Transform(*this);
	}

	void GameObject::render(const ShaderProgram& shaderProgram) {
		// Model matrix creation and upload

		shaderProgram.setMatrix4f("model", this->transform->getModelMatrix());

		renderFunction(*this);  // Should bind VAO
	}

	unsigned int GameObject::nextID = 0;
}