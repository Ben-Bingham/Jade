#include "High Level Rendering/PShaders/PShader.h"
//#include "High Level Rendering/ShaderCreator.h"

namespace Jade {
	ShaderProgram PShader::programInit(std::string vertexShaderPath, std::string fragmentShaderPath) {
		VertexShader vertexShader{ TextFile{vertexShaderPath} };
		FragmentShader fragmentShader{ TextFile{fragmentShaderPath} };

		return ShaderProgram{ vertexShader, fragmentShader };
	}

	ShaderProgram PShader::programInit(std::string vertexShaderPath, std::string geometryShaderPath, std::string fragmentShaderPath) {
		VertexShader vertexShader{ TextFile{vertexShaderPath} };
		GeometryShader geometryShader{ TextFile{geometryShaderPath} };
		FragmentShader fragmentShader{ TextFile{fragmentShaderPath} };

		return ShaderProgram{ vertexShader, geometryShader, fragmentShader };
	}
}