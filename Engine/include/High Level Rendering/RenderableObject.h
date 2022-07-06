#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"
#include "High Level Rendering/Transform.h"

namespace Jade {
	enum Model { //TODO how do i handle custom models
		CUBE,
		PYRAMID,
		CUSTOM
	};

	class RenderableObject {
	public:
		RenderableObject(Model shape = CUBE, glm::vec4 objectColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) 
			: m_VAO(), m_ObjectColour(objectColour), m_Shape(shape), m_VBO(vboInit()) {

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
		}

		bool followsRuleSet(RenderingRuleSet& ruleSet);

		void render(const RenderingRuleSet& ruleSet) const;

		void dispose() { m_VAO.dispose(); }

		VertexAttributeObject getVAO() { return m_VAO; }

		Transform& getTransform() { return m_Transform; }

	private:
		VertexAttributeObject m_VAO;
		Model m_Shape;
		VertexBufferObject m_VBO;
		glm::vec4 m_ObjectColour;
		Transform m_Transform;

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