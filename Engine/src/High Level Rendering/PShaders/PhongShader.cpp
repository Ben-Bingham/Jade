#include "High Level Rendering/PShaders/PhongShader.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void PhongShader::bindAdditionals() {
#ifdef JADE_DEBUG
		if (pointLights.size() == 0 && directionalLights.size() == 0) {
			LOG("No lights are active, scene will be dark.", WARNING);
		}
#endif // JADE_DEBUG

		getProgram().setDirectionalLights("directionalLights", directionalLights);
		getProgram().setPointLights("pointLights", pointLights);

		getProgram().setInt("shadowMap", 2);
		Texture::activateUnit(2);
		directionalLights[0].shadowMap.bind();

		directionalLights[0].makeLightSpaceMatrix();
		getProgram().setVector3f("cameraPosition", gCamera.getComponent<Transform>()->position);
		getProgram().setMatrix4f("lightSpaceMatrix", directionalLights[0].lightSpaceMatrix);
	}
}