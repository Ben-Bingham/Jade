#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "Low Level Rendering/Rendering Objects/Texture.h"

namespace Jade {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCordinates;
	};

	class Mesh {
	public:
		Mesh(const std::vector<Vertex>& verticies, const std::vector<unsigned int>& indicies, unsigned int materialIndex = 0)
			: m_Verticies(verticies), m_Indicies(indicies), m_MaterialIndex(materialIndex) {
		}

		Mesh() : m_Verticies(), m_Indicies(), m_MaterialIndex(0) {}

		std::vector<float> getVerticiesAsFloatVector() const {
			int numberOfFloatsInVertex = 8;

			std::vector<float> verticies(m_Verticies.size() * numberOfFloatsInVertex);

			memcpy(&verticies[0], &m_Verticies[0], m_Verticies.size() * numberOfFloatsInVertex * sizeof(float));

			return verticies;
		}

		std::vector<unsigned int> getIndicies() const { return m_Indicies; }
		std::vector<Vertex> getVerticies() const { return m_Verticies; }
		unsigned int getMaterialIndex() const { return m_MaterialIndex; }

	private:
		std::vector<Vertex> m_Verticies;
		std::vector<unsigned int> m_Indicies;
		unsigned int m_MaterialIndex;
	};
}