#pragma once

#include <GL/glew.h>

#include "Jade.h"

namespace Jade {
	class GLEW {
	public:
		GLEW() {
			if (glewInit() != GLEW_OK) {
				LOGGER.log("GLEW failed to initilize.", Jade::ERROR);
			}
		}
	};
}