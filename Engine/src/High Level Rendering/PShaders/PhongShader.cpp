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

		getProgram().setVector3f("cameraPosition", gCamera.getComponent<Transform>()->position);

		if (directionalLights.size() != 0) {
			getProgram().setInt("shadowMap", 2);
			Texture::activateUnit(2);
			directionalLights[0].shadowMap.bind();

			directionalLights[0].makeLightSpaceMatrix();
			getProgram().setMatrix4f("lightSpaceMatrix", directionalLights[0].lightSpaceMatrix); //TODO a lot of these uniforms can be moved to the scene class
		}
	}
}