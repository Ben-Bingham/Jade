#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "High Level Rendering/Rule Sets/RenderingRuleSet.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"
#include "High Level Rendering/Transform.h"

namespace Jade {
	enum Model {
		CUBE,
		PYRAMID,
		CUSTOM
	};

	class RenderableObject {
	public:
		RenderableObject(RuleSet ruleset, Model shape)
			: m_VAO(), m_Shape(shape), m_VBO(vboInit()), m_RuleSet(ruleset), m_NumberOfVerticies(numberOfVerticiesInit()) {

			init();
		}

		void render(const RenderingRuleSet& ruleSet) const {
			additionalRendering(ruleSet);

			ruleSet.getProgram().setMatrix4f("model", m_Transform.getMatrix());

			m_VAO.bind();

			glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerticies);
		}

		virtual void additionalRendering(const RenderingRuleSet& ruleSet) const = 0;

		bool followsRuleSet(const RenderingRuleSet& ruleSet) {
			return ruleSet.ruleSet == m_RuleSet;
		}

		VertexAttributeObject getVAO() { return m_VAO; }
		Transform& getTransform() { return m_Transform; }

		void dispose() { m_VAO.dispose(); }

	private:
		VertexAttributeObject m_VAO;
		Model m_Shape;
		VertexBufferObject m_VBO;
		Transform m_Transform;
		RuleSet m_RuleSet;
		int m_NumberOfVerticies;

		// EBO //TODO

		void init() {
			if (m_Shape == CUBE || m_Shape == PYRAMID) {
				VertexAttributePointer positionData(3, GL_FLOAT, POSITION);
				VertexAttributePointer normalData(3, GL_FLOAT, NORMAL);
				VertexAttributePointer textureCords(2, GL_FLOAT, TEXTURE_CORDINATE);

				std::vector<VertexAttributePointer> attributePointers = {
					positionData,
					normalData,
					textureCords
				};

				m_VAO.addAttributePointers(attributePointers);
			}
		}

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