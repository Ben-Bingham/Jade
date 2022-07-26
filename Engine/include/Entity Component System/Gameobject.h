#pragma once
#include <vector>
#include "Component.h"

namespace Jade {
	class Gameobject {
	public:
		Gameobject() : m_ID(getNextID()) {}

		void addComponent(Component* component) { m_Components.push_back(component); }
		Component* getComponent() {
			//TODO maybe with some kind of ID system for components and key value pairs
			// Could also brute force it and try to cast each Component to the specified type
		}


		void begin();
		void update();
		void cleanup();

	private:
		std::vector<Component*> m_Components;
		unsigned int m_ID;
		
		unsigned int getNextID() {
			staticID++;
			return staticID;
		}

		static unsigned int staticID;
	};
}