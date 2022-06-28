#pragma once

#include <memory>

namespace Jade {
	class Component {
	protected:
		Component(GameObject gameobject) {
			setGameObject(std::make_shared<GameObject>(std::move(gameobject)));
		}

	public:
		std::shared_ptr<GameObject> getGameObject() { return m_GameObject; }
		void setGameObject(std::shared_ptr<GameObject> gameobject) { m_GameObject = gameobject; }

	private:
		std::shared_ptr<GameObject> m_GameObject;
	};
}