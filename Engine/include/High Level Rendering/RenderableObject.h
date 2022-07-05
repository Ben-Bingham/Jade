#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "RenderingRuleSet.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"

namespace Jade {
	enum Primitive { //TODO how do i handel custom models
		CUBE
	};

	class RenderableObject {
	public:
		RenderableObject(Primitive shape = CUBE) : m_VAO(), m_ObjectColour(1.0f, 1.0f, 1.0f, 1.0f), m_Shape(shape), m_VBO(vboInit()) {
			
		}

		bool followsRuleSet(RenderingRuleSet& ruleSet) {
			//if this object contains at least all all the required rules in the rule set
			return true;
		}

		void render(const RenderingRuleSet& ruleSet) const {
			m_VAO.bind(); // bind VAO
			ruleSet.getProgram().setVector3f("objectColour", m_ObjectColour); // upload custom uniforms such as colour

			int numberOfVerticies = 0;
			switch (m_Shape) {
			case CUBE: numberOfVerticies = 36; break;
			}

			glDrawArrays(GL_TRIANGLES, 0, numberOfVerticies); // call the draw function
		}

		void dispose() { m_VAO.dispose(); }

	private:
		VertexAttributeObject m_VAO;
		Primitive m_Shape;
		VertexBufferObject m_VBO;
		glm::vec4 m_ObjectColour;

		// EBO //TODO
		// Possibly textures

		VertexBufferObject vboInit() {
			switch (m_Shape) {
			default:
			case CUBE: return VertexBufferObject(cubeVerticies);
			}
		}

		static std::vector<float> cubeVerticies;
	};
}