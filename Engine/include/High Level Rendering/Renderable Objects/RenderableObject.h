#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "High Level Rendering/Rule Sets/RenderingRuleSet.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"
#include "Low Level Rendering/Rendering Objects/ElementBufferObject.h"
#include "High Level Rendering/Transform.h"
#include "Core Systems/Resource Pipeline/Model.h"

namespace Jade {
	enum Shape {
		CUBE,
		PYRAMID,
		CUSTOM
	};

	class RenderableObject {
	public:
		RenderableObject(RuleSet ruleset, Mesh mesh)
			: m_Shape(CUSTOM), m_Mesh(mesh), m_VAO(), m_VBO(m_Mesh.getVerticiesAsFloatVector()), m_EBO(m_Mesh.getIndicies()), m_NumberOfIndicies((int)m_Mesh.getIndicies().size()), m_RuleSet(ruleset) {

			init();
		}

		RenderableObject(RuleSet ruleset, Shape shape)
			: m_Shape(shape), m_Mesh(meshInit()), m_VAO(), m_VBO(m_Mesh.getVerticiesAsFloatVector()), m_EBO(m_Mesh.getIndicies()), m_NumberOfIndicies((int)m_Mesh.getIndicies().size()), m_RuleSet(ruleset) {

			init();
		}

		void render(const RenderingRuleSet& ruleSet) const;

		virtual void additionalRendering(const RenderingRuleSet& ruleSet) const = 0;

		bool followsRuleSet(const RenderingRuleSet& ruleSet) {
			return ruleSet.ruleSet == m_RuleSet;
		}

		VertexAttributeObject getVAO() { return m_VAO; }
		Transform& getTransform() { return m_Transform; }

		void dispose() { m_VAO.dispose(); }

	private:
		Shape m_Shape;
		Mesh m_Mesh;
		VertexAttributeObject m_VAO;
		VertexBufferObject m_VBO;
		ElementBufferObject m_EBO;
		Transform m_Transform;
		RuleSet m_RuleSet;
		int m_NumberOfIndicies;

		void init() {
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

		Mesh meshInit() {
			switch (m_Shape) {
			default:
			case CUBE: return cubeMesh;
			case PYRAMID: return pyramidMesh;
			}
		}

		static Mesh cubeMesh;
		static Mesh pyramidMesh;
	};
}