#pragma once

#include "Low Level Rendering/Shaders/ShaderHeader.h"

namespace Jade {
	class RenderableObject;

	class RenderingRuleSet {
	public:
		RenderingRuleSet();

		void bind() { m_Program.use(); }

		bool Vertex_Positions = true;
		bool Vertex_Normals = false;
		bool Phong_Lighting = false;
		bool Object_Colour = false;

		void createProgram();

		int getID() const { return m_ID; }
		ShaderProgram getProgram() const { return m_Program; }

		bool allowsRenderable(RenderableObject& renderable);

	private:
		int m_ID;
		ShaderProgram m_Program;

		static int ID;

		static int getNextID() {
			ID++;
			return ID;
		}

		ShaderProgram programInit();

		void processRules() {
			if (Phong_Lighting) {
				Object_Colour = true;
				Vertex_Normals = true;
			}
		}
	};
}