#pragma once
#include <vector>
#include "Entity Component System/Components/Component.h"
#include "Entity Component System/Components/Transform.h"

namespace Jade {
	class Gameobject {
	public:
		Gameobject() : m_ID(getNextID()) {
			addComponent(new Transform()); //TODO delete
		}

		void addComponent(Component* component) { 
			component->setGameobject(this);
			m_Components.push_back(component);
		}

		template<typename T>
		T* getComponent() const {
			for (Component* component : m_Components) {
				T* desiredComponent = dynamic_cast<T*>(component);
				if (desiredComponent != nullptr) {
					return desiredComponent;
				}
			}
			return nullptr;
		}

		void addChild(Gameobject* gameobject) { m_Children.push_back(gameobject); }

		void begin();
		void update();
		void cleanup();

	private:
		std::vector<Component*> m_Components;
		std::vector<Gameobject*> m_Children;

		unsigned int m_ID;
		
		unsigned int getNextID() {
			staticID++;
			return staticID;
		}

		static unsigned int staticID;
	};
}