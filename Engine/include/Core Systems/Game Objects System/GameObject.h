#pragma once

#include <vector>
#include <memory>

#include "Jade.h"

namespace Jade {
	class Component;
	class Transform;
	class ShaderProgram;
	class Renderer;

	class GameObject {
	public:
		GameObject();
		GameObject(const GameObject&) = default;
		GameObject(GameObject&&) = default;
		GameObject& operator=(const GameObject&) = default;
		GameObject& operator=(GameObject&&) = default;
		~GameObject() {
			delete renderer;
			delete transform;
		}


		Renderer* renderer;
		Transform* transform;
		void (*renderFunction)(GameObject& gameObject);

		void render(const ShaderProgram& shaderProgram);

		void setRenderFunction(void (*newRenderFunction)(GameObject& gameObject)) { renderFunction = newRenderFunction; }

		unsigned int getID() { return m_ID; }

	private:
		unsigned int m_ID;

		static unsigned int nextID;
		static unsigned int getNextID() {
			nextID++;
			return nextID;
		}
	};
}