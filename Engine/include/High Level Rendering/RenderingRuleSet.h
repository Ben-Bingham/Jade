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
		RenderingRuleSet(RuleSet rules = STANDARD);

		void bind() { m_Program.use(); }

		RuleSet ruleSet;

		void createProgram();

		int getID() const { return m_ID; }
		ShaderProgram getProgram() const { return m_Program; }

		Light getLight() { return m_Light; }

		void dispose() {
			m_Program.dispose();
		}

	private:
		int m_ID;
		ShaderProgram m_Program;
		Light m_Light; //TODO allow multiple lights

		static int ID;

		static int getNextID() {
			ID++;
			return ID;
		}

		ShaderProgram programInit();
	};
}