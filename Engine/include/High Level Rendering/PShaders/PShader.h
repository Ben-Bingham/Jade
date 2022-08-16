#pragma once
#include <vector>

#include "Low Level Rendering/Shaders/ShaderProgram.h"

namespace Jade {
	class RenderableObject;

	enum ShaderType { //TODO remove
		SOLID_COLOUR,
		PHONG,
		DIRECTIONAL_SHADOW_MAP,
		POINT_SHADOW_MAP,
		SKYBOX
	};

	class PShader { //TODO rename to practicle shader
	public:
		PShader(std::string vertexShaderPath, std::string fragmentShaderPath) 
			: m_Program(programInit(vertexShaderPath, fragmentShaderPath)) {}

		PShader(std::string vertexShaderPath, std::string geometryShaderPath, std::string fragmentShaderPath) 
			: m_Program(programInit(vertexShaderPath, geometryShaderPath, fragmentShaderPath)) {}

		void bind() { 
			m_Program.use();
		}

		virtual void uploadUniforms() = 0;

		ShaderProgram getProgram() const { return m_Program; }

		void dispose() { 
			m_Program.dispose();
		}

	private:
		ShaderProgram m_Program;

		ShaderProgram programInit(std::string vertexShaderPath, std::string fragmentShaderPath);
		ShaderProgram programInit(std::string vertexShaderPath, std::string geometryShaderPath, std::string fragmentShaderPath);
	};
}