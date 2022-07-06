#include <vector>

#include "High Level Rendering/RenderableObject.h"

namespace Jade {
	bool RenderableObject::followsRuleSet(RenderingRuleSet& ruleSet) {
		bool hasPosition = false;
		bool hasNormals = false;
		std::vector<VertexAttributePointer>::iterator it;
		std::vector<VertexAttributePointer> attributes = m_VAO.getAttributePointers();
		for (it = attributes.begin(); it != attributes.end(); it++) {
			if (it->name == POSITION) {
				hasPosition = true;
			}

			if (it->name == NORMAL) {
				hasNormals = true;
			}
		}

		if (
			ruleSet.Vertex_Normals == hasNormals &&
			ruleSet.Vertex_Positions == hasPosition &&
			(hasNormals && hasPosition) == ruleSet.Phong_Lighting
			) {
			return true;
		}
		else {
			return false;
		}
	}

	void RenderableObject::render(const RenderingRuleSet& ruleSet) const {
		ruleSet.getProgram().setVector3f("objectColour", m_ObjectColour);
		ruleSet.getProgram().setMatrix4f("model", m_Transform.getMatrix());

		m_VAO.bind();

		int numberOfVerticies = 0;
		switch (m_Shape) {
		case CUBE: numberOfVerticies = 36; break;
		}

		glDrawArrays(GL_TRIANGLES, 0, numberOfVerticies);
	}

	std::vector<float> RenderableObject::cubeVerticies = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};
}