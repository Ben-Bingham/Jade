#pragma once

#include <vector>
#include <memory>

#include "Jade.h"

namespace Jade {
	class Component;

	class GameObject {
	public:
		GameObject();

		void setRenderFunction(void (*renderFunction)(GameObject& gameoObject)) {
			m_RenderFunction = renderFunction;
		}

		void render() {
			m_RenderFunction(*this);
		}
		
		void addComponent(std::shared_ptr<Component> component) { m_Components.push_back(component); }

	private:
		std::vector<std::shared_ptr<Component>> m_Components;
		unsigned int m_ID;
		void (*m_RenderFunction)(GameObject& gameoObject);

		static unsigned int nextID;

		static unsigned int getNextID() {
			nextID++;
			return nextID;
		}
	};

	
}