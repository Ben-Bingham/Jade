#pragma once

#include <vector>

#include "Jade.h"

#include "GameObject.h"
#include "Low Level Rendering/Shaders/ShaderProgram.h"
#include <Core Systems/Components/Transform.h>

namespace Jade {
	class Scene {
	public:
		Scene() : m_GameObjects() {}

		void render(const ShaderProgram& shaderProgram) {
			//TODO upload other matricies

			std::vector<GameObject>::iterator it;
			for (it = m_GameObjects.begin(); it != m_GameObjects.end(); it++) {
				it->render(shaderProgram);
			}
		}

		void addGameObject(GameObject& gameObject) {
			m_GameObjects.push_back(gameObject);
		}

	private:
		std::vector<GameObject> m_GameObjects;

	};
}