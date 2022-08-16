#include "Engine Structure/Subsystems/Renderer.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void Renderer::renderNormally(std::vector<std::shared_ptr<RenderableObject>> renderables, std::vector<std::shared_ptr<Light>> lights) {
		glClearColor(0.549f, 0.549f, 0.549f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, gWindow.getWidth(), gWindow.getHeight());

		for (std::shared_ptr<RenderableObject> renderable : renderables) {
			renderObject(renderable, phongShader);
		}
	}
}