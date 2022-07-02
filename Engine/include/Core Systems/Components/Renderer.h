#pragma once

#include <vector>

#include "Core Systems/Game Objects System/GameObject.h"
#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"
#include "Low Level Rendering/Rendering Objects/VertexBufferObject.h"

namespace Jade {
	extern std::vector<float> cubeVertices;

	extern void nullRender(GameObject& gameObject);
	extern void cubeRender(GameObject& gameObject);

	class Renderer {
	public:
		Renderer(GameObject& gameObject, std::vector<float> verticies);

		VertexAttributeObject getVAO() { return m_VAO; }

	private:
		GameObject m_GameObject;
		std::vector<float> m_Verticies;
		VertexAttributeObject m_VAO;
		VertexBufferObject m_VBO;
	};

	class CubeRenderer : public Renderer {
	public:
		CubeRenderer(GameObject& gameObject) : Renderer(gameObject, cubeVertices) {
			gameObject.setRenderFunction(cubeRender);
		}
	};
}