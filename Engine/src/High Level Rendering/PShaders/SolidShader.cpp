#include "High Level Rendering/PShaders/SolidShader.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	void SolidShader::uploadUniforms() {
		getProgram().setMatrix4f("view", gCamera.getViewMatrix());
		getProgram().setMatrix4f("projection", gWindow.getProjectionMatrix());
	}
}