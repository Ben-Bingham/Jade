#pragma once
#include <vector>
#include "Entity Component System/Components/Component.h"
#include "Entity Component System/Components/Transform.h"

namespace Jade {
	class Gameobject {
	public:
		Gameobject() : m_ID(getNextID()) {
			addComponent(Transform{});
		}

		template<typename T>
		void addComponent(T& component) { 
			m_Components.push_back(std::make_shared<T>(component));
			m_Components[m_Components.size() - 1]->setGameobject(std::make_shared<Gameobject>(*this));
		}

		template<typename T>
		T* getComponent() const {
			for (std::shared_ptr<Component> component : m_Components) {
				T* desiredComponent = dynamic_cast<T*>(component.get());
				if (desiredComponent != nullptr) {
					return desiredComponent;
				}
			}
			return nullptr;
		}

		void addChild(const Gameobject& gameobject) { m_Children.push_back(std::make_shared<Gameobject>(gameobject)); }

		std::vector<std::shared_ptr<Gameobject>> getChildren() { return m_Children; }

		void begin();
		void update();
		void cleanup();

	private:
		std::vector<std::shared_ptr<Component>> m_Components;
		std::vector<std::shared_ptr<Gameobject>> m_Children; //TODO testing

		unsigned int m_ID;
		
		unsigned int getNextID() {
			staticID++;
			return staticID;
		}

		static unsigned int staticID;
	};
}