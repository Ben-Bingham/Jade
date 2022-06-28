#include <memory>

#include "Core Systems/Game Objects System/GameObject.h"
#include "Core Systems/Components/Transform.h"

#include "Jade.h"

namespace Jade {
	GameObject::GameObject() : m_ID(getNextID()) {
		addComponent(std::make_shared<Transform>(*this));
		setRenderFunction(nullptr);
	}

	unsigned int GameObject::nextID = 0;
}