#include "High Level Rendering/PShaders/PhongShader.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void PhongShader::uploadUniforms() {
		bind();
#ifdef JADE_DEBUG
		if (m_Lights.size() < 0) {
			LOG("No lights are active, scene will be dark.", WARNING);
		}
#endif // JADE_DEBUG

		std::vector<PointLight> pointLights;
		std::vector<DirectionalLight> dirLights;
		for (std::shared_ptr<Light> light : m_Lights) {
			DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(&*light);
			PointLight* pointLight = dynamic_cast<PointLight*>(&*light);
			if (dirLight != nullptr) {
				dirLights.push_back(*dirLight);
			}
			if (pointLight != nullptr) {
				pointLights.push_back(*pointLight);
			}
		}

		getProgram().setDirectionalLights("directionalLights", dirLights);
		getProgram().setPointLights("pointLights", pointLights);

		getProgram().setVector3f("cameraPosition", gCamera.getComponent<Transform>()->position);

		getProgram().setMatrix4f("view", gCamera.getViewMatrix());
		getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());

		if (dirLights.size() != 0) {
			getProgram().setInt("shadowMap", 3);
			Texture::activateUnit(3);
			dirLights[0].shadowMap.bind();

			dirLights[0].makeLightSpaceMatrix();
			getProgram().setMatrix4f("lightSpaceMatrix", dirLights[0].lightSpaceMatrix); //TODO a lot of these uniforms can be moved to the scene class
		}

		if (pointLights.size() != 0) {
			getProgram().setInt("pointShadowMap", 4);
			Texture::activateUnit(4);
			pointLights[0].shadowMap.bind();

			getProgram().setFloat("farPlane", pointLights[0].farPlane);
		}
	}
}