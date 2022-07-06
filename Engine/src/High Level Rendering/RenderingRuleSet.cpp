#include "High Level Rendering/RenderingRuleSet.h"
#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include <High Level Rendering/RenderableObject.h>

namespace Jade {
	RenderingRuleSet::RenderingRuleSet() : m_Program(programInit()), m_ID(getNextID()) {}

	void RenderingRuleSet::createProgram() {
		processRules();
		m_Program.dispose();
		ShaderCreator creator(*this);
		m_Program = creator.createProgram();
		creator.dispose();
	}

	bool RenderingRuleSet::allowsRenderable(RenderableObject& renderable) {
		bool hasPosition = false;
		bool hasNormals = false;
		std::vector<VertexAttributePointer>::iterator it;
		std::vector<VertexAttributePointer> attributes = renderable.getVAO().getAttributePointers();
		for (it = attributes.begin(); it != attributes.end(); it++) {
			if (it->name == POSITION) {
				hasPosition = true;
			}

			if (it->name == NORMAL) {
				hasNormals = true;
			}
		}

		if (
			this->Vertex_Normals == hasNormals &&
			this->Vertex_Positions == hasPosition ||
			(hasNormals && hasPosition) == this->Phong_Lighting
			) {
			return true;
		}
		else {
			return false;
		}
	}

	ShaderProgram RenderingRuleSet::programInit() {
		ShaderCreator creator(*this);
		ShaderProgram program(creator.createProgram());
		return program;
	}

	int RenderingRuleSet::ID = -1;
}