#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "High Level Rendering/PShaders/PShader.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"
#include "Low Level Rendering/Rendering Objects/ElementBufferObject.h"
#include "Core Systems/Resource Pipeline/Model.h"
#include "Entity Component System/Components/Transform.h"

namespace Jade {
	enum Shape {
		CUBE,
		PYRAMID,
		CUSTOM
	};

	class RenderableObject {
	public:
		RenderableObject(ShaderType ruleset, Mesh mesh)
			: m_Shape(CUSTOM), m_Mesh(mesh), m_VAO(), m_VBO(m_Mesh.getVerticiesAsFloatVector()), m_EBO(m_Mesh.getIndicies()), m_NumberOfIndicies((int)m_Mesh.getIndicies().size()), m_RuleSet(ruleset) {

			init();
		}

		RenderableObject(ShaderType ruleset, Shape shape)
			: m_Shape(shape), m_Mesh(meshInit()), m_VAO(), m_VBO(m_Mesh.getVerticiesAsFloatVector()), m_EBO(m_Mesh.getIndicies()), m_NumberOfIndicies((int)m_Mesh.getIndicies().size()), m_RuleSet(ruleset) {

			init();
		}

		void render(const PShader& shader);
		void render(const PShader& ruleSet, ShaderProgram shader);

		virtual void additionalRendering(const PShader& ruleSet) const = 0;

		bool followsRuleSet(const PShader& ruleSet) {
			return ruleSet.ruleSet == m_RuleSet;
		}

		VertexAttributeObject getVAO() { return m_VAO; }

		void dispose() { m_VAO.dispose(); }

	private:
		Shape m_Shape;
		Mesh m_Mesh;
		VertexAttributeObject m_VAO;
		VertexBufferObject m_VBO;
		ElementBufferObject m_EBO;
		ShaderType m_RuleSet;
		int m_NumberOfIndicies;
		glm::mat4 m_ModelMatrix{ 1.0f };

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