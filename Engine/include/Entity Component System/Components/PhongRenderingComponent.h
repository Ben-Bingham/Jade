#pragma once
#include "Entity Component System/Component.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"

using std::make_unique;
using std::unique_ptr;

namespace Jade {
	class Application;

	class PhongRenderingComponent : public Component { //TODO the name sucks
	public:
		PhongRenderingComponent(Model* model) {
			for (const Jade::AssimpMaterial& material : model->getMaterials()) {
				m_Materials.push_back(Jade::Material(material));
			}

			for each (Jade::Mesh mesh in model->getMeshes()) {
				m_Renderables.push_back(PhongRenderable(&m_Materials[mesh.getMaterialIndex()], mesh));
			}
		}

		void addRenderables(Application& app); //TODO make it so i add the renderables to a renderer not an app

	private:
		std::vector<PhongRenderable> m_Renderables;
		std::vector<Material> m_Materials;
	};
}