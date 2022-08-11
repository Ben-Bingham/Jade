#pragma once
#include <vector>

#include "Low Level Rendering/Shaders/ShaderProgram.h"

namespace Jade {
	class RenderableObject;

	enum ShaderType {
		SOLID_COLOUR,
		PHONG,
		DIRECTIONAL_SHADOW_MAP,
		POINT_SHADOW_MAP,
		SKYBOX
	};

	class PShader {
	public:
		//PShader(ShaderType rules);

		PShader(std::string vertexShaderPath, std::string fragmentShaderPath) 
			: m_Program(programInit(vertexShaderPath, fragmentShaderPath)) {}

		PShader(std::string vertexShaderPath, std::string geometryShaderPath, std::string fragmentShaderPath) 
			: m_Program(programInit(vertexShaderPath, geometryShaderPath, fragmentShaderPath)) {}

		void bind() { 
			m_Program.use();
		}

		// Should bind anything that is specific to the shader
		virtual void bindAdditionals() = 0;

		//int getID() const { return m_ID; }
		ShaderProgram getProgram() const { return m_Program; }

		void dispose() { 
			m_Program.dispose();
			//TODO dispose shgaders
		}

		void addPointLight(const PointLight& light) {
			pointLights.push_back(light);
		}

		void addDirectionalLight(const DirectionalLight& light) {
			directionalLights.push_back(light);
		}

		void clearLights() {
			pointLights.clear();
			directionalLights.clear();
		}

		ShaderType ruleSet;

		std::vector<PointLight> pointLights; //TODO remove
		std::vector<DirectionalLight> directionalLights; //TODO remove
	private:
		//int m_ID;
		ShaderProgram m_Program;

		ShaderProgram programInit(std::string vertexShaderPath, std::string fragmentShaderPath);
		ShaderProgram programInit(std::string vertexShaderPath, std::string geometryShaderPath, std::string fragmentShaderPath);

	/*	static int ID;

		static int getNextID() {
			ID++;
			return ID;
		}*/

		//ShaderProgram programInit();
	};
}