#pragma once

#include "High Level Rendering/Renderable Objects/RenderableObject.h"
#include "Low Level Rendering/Rendering Objects/Cubemap.h"

namespace Jade {
	class SkyboxRenderableObject : public RenderableObject {
	public:
		SkyboxRenderableObject(std::vector<Image> images)
			: RenderableObject(SKYBOX, CUBE), cubemap(images) {
		}

	private:
		std::shared_ptr<Material> m_Material;
		Cubemap cubemap;
	};
}