#pragma once
#include <vector>

#include "Low Level Rendering/Shaders/ShaderHeader.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class RenderableObject;

	enum RuleSet {
		STANDARD, // Vertex postions, and normals along with static object colour, implemets Phong lighting
		TEXTURE,  // Same as standard but has tex cords and textures aswell, implemets Phong lighting
		SOLID_COLOUR // Vertex postions, along with static object colour, implemets No lighting
	};

	class RenderingRuleSet {
	public:
		RenderingRuleSet(RuleSet rules);

		void bind() { 
			m_Program.use();
			bindAdditionals();
		}

		virtual void bindAdditionals() = 0;

		void createProgram();
		

		//void addLight(const Light& light) {
		//	if (ruleSet == STANDARD || ruleSet == TEXTURE) {
		//		m_Lights.push_back(light);
		//	}
		//	else {
		//		std::string message = "The rule set with ID: ";
		//		message += std::to_string(m_ID);
		//		message += "does not support lights.";
		//		LOGGER.log(message, Jade::WARNING);
		//	}
		//}

		void dispose() {
			m_Program.dispose();
		}

		//std::vector<Light> getLights() { return m_Lights; }

		int getID() const { return m_ID; }

		ShaderProgram getProgram() const { return m_Program; }

		RuleSet ruleSet;

	private:
		int m_ID;
		ShaderProgram m_Program;
		//Light m_Light; //TODO allow multiple lights
		//std::vector<Light> m_Lights;

		static int ID;

		static int getNextID() {
			ID++;
			return ID;
		}

		ShaderProgram programInit();
	};
}