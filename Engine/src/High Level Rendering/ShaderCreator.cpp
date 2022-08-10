#include "Core Systems/Logging/Log.h"

#include "High Level Rendering/ShaderCreator.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	VertexShader ShaderCreator::vertexShaderInit() {
		std::string vertexShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) {
		default:
		case SOLID_COLOUR: vertexShaderPath += "SolidRuleSet.vert"; break;
		case PHONG: vertexShaderPath += "PhongRuleSet.vert"; break;
		case DIRECTIONAL_SHADOW_MAP: vertexShaderPath += "DirectionalDepthShader.vert"; break;
		case POINT_SHADOW_MAP: vertexShaderPath += "PointDepthShader.vert"; break;
		case SKYBOX: vertexShaderPath += "SkyboxShader.vert"; break;
		}

		TextFile vertexShaderFile(vertexShaderPath);

		return VertexShader(vertexShaderFile);
	}

	FragmentShader ShaderCreator::fragmentShaderInit() {
		std::string fragmentShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) {
		default:
		case SOLID_COLOUR: fragmentShaderPath += "SolidRuleSet.frag"; break;
		case PHONG: fragmentShaderPath += "PhongRuleSet.frag"; break;
		case DIRECTIONAL_SHADOW_MAP: fragmentShaderPath += "DirectionalDepthShader.frag"; break;
		case POINT_SHADOW_MAP: fragmentShaderPath += "PointDepthShader.frag"; break;
		case SKYBOX: fragmentShaderPath += "SkyboxShader.frag"; break;
		}

		TextFile fragmentShaderFile(fragmentShaderPath);

		return FragmentShader(fragmentShaderFile);
	}

	GeometryShader ShaderCreator::geometryShaderInit() {
		std::string geometryShaderPath = "..\\Engine\\assets\\shaders\\";

		switch (m_RuleSet->ruleSet) {
		default:
		case POINT_SHADOW_MAP: geometryShaderPath += "PointDepthShader.geom"; break;
		}

		TextFile geometryShaderFile(geometryShaderPath);

		return GeometryShader(geometryShaderFile);
	}
}