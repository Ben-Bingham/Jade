#include "Engine Structure/Engine.h"
#include "Engine Structure/Scene.h"

namespace Jade {
	Time gTime{};
	Window gWindow{};
	Keyboard gKeyboard{};
	Mouse gMouse{};
	GLEW gGlew{};
	Camera gCamera{};
	Renderer gRenderer{};
}