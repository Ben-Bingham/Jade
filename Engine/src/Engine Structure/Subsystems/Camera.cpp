#include "Engine Structure/Subsystems/Camera.h"
#include "Engine Structure/Engine.h"

namespace Jade {
	Camera::Camera(float fov, glm::vec3 position, glm::vec3 worldUp)
		: m_WorldUp(worldUp), front(glm::vec3(0.0f, 0.0f, -1.0f)), m_FOV(fov) {

		updateCameraVectors();
		gWindow.disableCursor();
	}
}
