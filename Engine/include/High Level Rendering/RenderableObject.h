#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"
#include "High Level Rendering/Transform.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"
#include "High Level Rendering/MaterialCreator.h"

namespace Jade {
	enum Model {
		CUBE,
		PYRAMID,
		CUSTOM
	};

	class RenderableObject {
	public:
		RenderableObject(Model shape = CUBE, glm::vec4 objectColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), RuleSet ruleset = STANDARD) 
			: m_VAO(), m_ObjectColour(objectColour), m_Shape(shape), m_VBO(vboInit()), m_RuleSet(ruleset), m_Material(MaterialCreator::DefaultMaterial()), m_NumberOfVerticies(numberOfVerticiesInit()) {

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
		int m_NumberOfVerticies;

		// EBO //TODO
		// Possibly textures

		VertexBufferObject vboInit() {
			switch (m_Shape) {
			default:
			case CUBE: return VertexBufferObject(cubeVerticies);
			case PYRAMID: return VertexBufferObject(pyramidVerticies);
			}
		}

		int numberOfVerticiesInit() {
			switch (m_Shape) {
			default:
			case CUBE: return 36;
			case PYRAMID: return 18;
			}
		}

		static std::vector<float> cubeVerticies;
		static std::vector<float> pyramidVerticies;
	};
}