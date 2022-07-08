#pragma once
#include <vector>

#include "Low Level Rendering/Shaders/ShaderHeader.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"

namespace Jade {
	class RenderableObject;

	enum RuleSet {
		STANDARD, // Vertex postions, and normals along with material, implemets Phong lighting
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

		int getID() const { return m_ID; }

		ShaderProgram getProgram() const { return m_Program; }

		void dispose() { m_Program.dispose(); }

		RuleSet ruleSet;
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