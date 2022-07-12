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
		RenderableObject(RuleSet ruleset, Shape shape)
			: m_VAO(), m_Shape(shape), m_VBO(vboInit()), m_RuleSet(ruleset), m_NumberOfIndicies(numberOfVerticiesInit()), m_EBO(eboInit()), m_Mesh(std::vector<Vertex>{{glm::vec3(1.0), glm::vec3(1.0), glm::vec3(1.0)}}, std::vector<unsigned int>{1}, std::vector<TextureStruct>{ {1, "type", "Path"}}) {

			init();
		}

		RenderableObject(RuleSet ruleset, Mesh mesh)
			: m_VAO(), m_Shape(CUSTOM), m_VBO(vboInit()), m_RuleSet(ruleset), m_NumberOfIndicies(numberOfVerticiesInit()), m_EBO(eboInit()), m_Mesh(mesh) {

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
		Mesh m_Mesh;
		Shape m_Shape;
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

		VertexBufferObject vboInit() {
			switch (m_Shape) {
			default:
			case CUBE: return VertexBufferObject(cubeVerticies);
			case PYRAMID: return VertexBufferObject(pyramidVerticies);
			case CUSTOM: return VertexBufferObject(m_Mesh.getVerticies());
			}
		}

		ElementBufferObject eboInit() {
			switch (m_Shape) {
			default:
			case CUBE: return ElementBufferObject(cubeIndicies);
			case PYRAMID: return ElementBufferObject(pyramidIndicies);
			case CUSTOM: return ElementBufferObject(m_Mesh.getIndicies());
			}
		}

		int numberOfVerticiesInit() {
			switch (m_Shape) {
			default:
			case CUBE: return 36;
			case PYRAMID: return 18;
			case CUSTOM: return m_Mesh.getIndicies().size();
			}
		}

		static std::vector<float> cubeVerticies;
		static std::vector<unsigned int> cubeIndicies;

		static std::vector<float> pyramidVerticies;
		static std::vector<unsigned int> pyramidIndicies;
	};
}