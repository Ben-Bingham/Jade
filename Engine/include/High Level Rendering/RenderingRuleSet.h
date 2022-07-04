#pragma once

#include "Low Level Rendering/Shaders/ShaderHeader.h"

namespace Jade {
	class RenderingRuleSet {
	public:
		RenderingRuleSet();

		void bind() { m_Program.use(); }

		bool Vertex_Positions = true;
		bool Vertex_Normals = false;
		bool Phong_Lighting = false;
		bool Object_Colour = false;

		void createProgram();

		int getID() { return m_ID; }

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