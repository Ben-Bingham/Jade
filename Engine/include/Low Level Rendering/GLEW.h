#pragma once

#include <GL/glew.h>

#include "Jade.h"

namespace Jade {
	class GLEW {
	public:
		GLEW() {
			if (glewInit() != GLEW_OK) {
				LOG("GLEW failed to initilize.", Jade::ERROR);
			}
		}
	};
}