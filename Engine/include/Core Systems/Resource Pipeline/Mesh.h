#pragma once
#include <vector>

#include <glm/glm.hpp>

namespace Jade {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCordinates;

		std::vector<float> getAsFloatVector() {
			std::vector<float> floats;
			floats.push_back(position.x);
			floats.push_back(position.y);
			floats.push_back(position.z);
			floats.push_back(normal.x);
			floats.push_back(normal.y);
			floats.push_back(normal.z);
			floats.push_back(textureCordinates.x);
			floats.push_back(textureCordinates.y);
			return floats;
		}
	};

	struct TextureStruct {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		Mesh(const std::vector<Vertex>& verticies, const std::vector<unsigned int>& indicies, const std::vector<TextureStruct>& textures)
			: m_Verticies(verticies), m_Indicies(indicies), m_Textures(textures) {
		}

		std::vector<float> getVerticies() const {
			std::vector<float> verticies;
			std::vector<float> vert;
			for each (Vertex vertex in m_Verticies) {
				vert = vertex.getAsFloatVector();
				verticies.insert(verticies.end(), vert.begin(), vert.end());
			}
			return verticies;
		}
		std::vector<unsigned int> getIndicies() const { return m_Indicies; }

	private:
		std::vector<Vertex> m_Verticies;
		std::vector<unsigned int> m_Indicies;
		std::vector<TextureStruct> m_Textures;
	};
}