#include "Jade.h"

#include "DemoScene.h"

int main() {
	Jade::Engine engine{};
	engine.StartUp();

	DemoScene scene{};

	engine.LoadScene(scene);

	engine.ShutDown();
	return 0;
}
