#include "High Level Rendering/Renderable Objects/SkyboxRenderableObject.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void SkyboxRenderableObject::additionalRendering(const PShader& shader) const {
		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);
		Texture::activateUnit(0);
		shader.getProgram().setInt("skybox", 0);
		cubemap.bind();

		glm::mat4 view = glm::mat4(glm::mat3(gCamera.getViewMatrix()));

		shader.getProgram().setMatrix4f("view", view);
		shader.getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());
	}
}