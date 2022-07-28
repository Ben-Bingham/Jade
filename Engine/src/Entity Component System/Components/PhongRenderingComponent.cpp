#include "Entity Component System/Components/PhongRenderingComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	PhongRenderingComponent::PhongRenderingComponent(Model* model) {
		for (const Jade::AssimpMaterial& material : model->getMaterials()) {
			m_Materials.push_back(Jade::Material(material));
		}

		for each (Jade::Mesh mesh in model->getMeshes()) {
			renderables.push_back(new PhongRenderable(&m_Materials[mesh.getMaterialIndex()], mesh)); //TODO delete
		}
	}
}