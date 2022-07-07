#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"
#include "High Level Rendering/Transform.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	enum Model { //TODO how do i handle custom models
		CUBE,
		PYRAMID,
		CUSTOM
	};

	class RenderableObject {
	public:
		RenderableObject(Model shape = CUBE, glm::vec4 objectColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) 
			: m_VAO(), m_ObjectColour(objectColour), m_Shape(shape), m_VBO(vboInit()), m_RuleSet(STANDARD), m_Material() {

			if (m_Shape == CUBE || m_Shape == PYRAMID) {
				VertexAttributePointer positionData(3, GL_FLOAT, POSITION);
				VertexAttributePointer normalData(3, GL_FLOAT, NORMAL);

				std::vector<VertexAttributePointer> attributePointers = {
					positionData,
					normalData
				};

				m_VAO.addAttributePointers(attributePointers);
			}
			else {
				VertexAttributePointer positionData(3, GL_FLOAT, POSITION);

				m_VAO.setAttributePointer(positionData);
			}

			m_Material.ambient = glm::vec3(1.0f, 0.5f, 0.31f); // TODO make somesort of class that gives default materials
			m_Material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
			m_Material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
			m_Material.shininess = 32.0f;
		}

		void render(const RenderingRuleSet& ruleSet) const;

		void dispose() { m_VAO.dispose(); }

		VertexAttributeObject getVAO() { return m_VAO; }

		Transform& getTransform() { return m_Transform; }

		bool followsRuleSet(const RenderingRuleSet& ruleSet) {
			return ruleSet.ruleSet == m_RuleSet;
		}

	private:
		VertexAttributeObject m_VAO;
		Model m_Shape;
		VertexBufferObject m_VBO;
		glm::vec4 m_ObjectColour;
		Transform m_Transform;
		RuleSet m_RuleSet;
		Material m_Material;

		// EBO //TODO
		// Possibly textures

		VertexBufferObject vboInit() {
			switch (m_Shape) {
			default:
			case CUBE: return VertexBufferObject(cubeVerticies);
			case PYRAMID: return VertexBufferObject(pyramidVerticies);
			}
		}

		static std::vector<float> cubeVerticies;
		static std::vector<float> pyramidVerticies;
	};
}