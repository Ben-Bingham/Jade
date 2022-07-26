#pragma once
#include <vector>

#include "Low Level Rendering/Shaders/ShaderProgram.h"
#include "Low Level Rendering/Shaders/ShaderStructs.h"

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

		ShaderType ruleSet;
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