#pragma once

#include "Low Level Rendering/Shaders/ShaderHeader.h"

namespace Jade {
	class RenderableObject;

	enum RuleSet {
		STANDARD, // Vertex postions, and normals along with static object colour, implemets Phong lighting
		TEXTURE	  // Same as standard but has tex cords and textures aswell, implemets Phong lighting
	};

	class RenderingRuleSet {
	public:
		RenderingRuleSet(RuleSet rules = STANDARD);

		void bind() { m_Program.use(); }

		RuleSet ruleSet;

		void createProgram();

		int getID() const { return m_ID; }
		ShaderProgram getProgram() const { return m_Program; }

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