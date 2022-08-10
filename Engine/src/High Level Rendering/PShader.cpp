#include "High Level Rendering/PShaders/PShader.h"
#include "High Level Rendering/ShaderCreator.h"

namespace Jade {
	PShader::PShader(ShaderType rules)
		: m_Program(programInit()), m_ID(getNextID()), ruleSet(rules) {}

	ShaderProgram PShader::programInit() {
		ShaderCreator creator(this);
		if (ruleSet == POINT_SHADOW_MAP) {
			return ShaderProgram(creator.getFragmentShader(), creator.getVertexShader(), creator.getGeometryShader());
		}
		return ShaderProgram(creator.getFragmentShader(), creator.getVertexShader());
	}

	int PShader::ID = -1;
}