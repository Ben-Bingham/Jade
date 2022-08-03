#include "Entity Component System/Components/Rendering Components/PhongRenderingComponent.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	PhongRenderingComponent::PhongRenderingComponent(Model& model) {
		shader = std::make_shared<PhongShader>();

		for (const Jade::AssimpMaterial& material : model.getMaterials()) {
			m_Materials.push_back(std::make_shared<Material>(material));
		}

		for (Jade::Mesh mesh : model.getMeshes()) {
			renderables.push_back(std::make_shared<PhongRenderable>(m_Materials[mesh.getMaterialIndex()], mesh));
		}
	}

	PhongRenderingComponent::PhongRenderingComponent(Shape shape, const Material& material) {
		shader = std::make_shared<PhongShader>();

		m_Materials.push_back(std::make_shared<Material>(material));

		renderables.push_back(std::make_shared<PhongRenderable>(m_Materials[0], shape));
	}

	void PhongRenderingComponent::Render() {
		shader->getProgram().setVector3f("cameraPosition", gCamera.getComponent<Transform>()->position);
	}
}