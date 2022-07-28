#pragma once
#include "Entity Component System/Component.h"
#include "Entity Component System/Components/RenderComponent.h"
#include "High Level Rendering/Renderable Objects/PhongRenderableObject.h"
#include "High Level Rendering/PShaders/PhongShader.h"
#include "High Level Rendering/Renderable Objects/SolidRenderableObject.h"

namespace Jade {
	class Application;

	class PhongRenderingComponent : public RenderComponent { //TODO the name sucks
	public:
		PhongRenderingComponent(Model* model);

	private:
		std::vector<Material> m_Materials;
	};
}