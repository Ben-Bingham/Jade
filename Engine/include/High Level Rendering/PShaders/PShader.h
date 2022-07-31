#pragma once
#include <vector>

#include "Low Level Rendering/Shaders/ShaderProgram.h"

namespace Jade {
	class RenderableObject;

	enum ShaderType {
		SOLID_COLOUR,	// Solid shading
		PHONG			// Phong shading
	};

	class PShader {
	public:
		PShader(ShaderType rules);

		void bind() { 
			m_Program.use();
		}

		virtual void bindAdditionals() = 0;

		int getID() const { return m_ID; }
		ShaderProgram getProgram() const { return m_Program; }

		void dispose() { m_Program.dispose(); }

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

		std::vector<PointLight> pointLights;
		std::vector<DirectionalLight> directionalLights;
	private:
		int m_ID;
		ShaderProgram m_Program;

		static int ID;

		static int getNextID() {
			ID++;
			return ID;
		}

		ShaderProgram programInit();
	};
}