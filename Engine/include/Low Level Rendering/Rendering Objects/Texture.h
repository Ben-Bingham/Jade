#pragma once

#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Image.h"

namespace Jade {
	class Texture {
	public:
		Texture(const Jade::Image& image);

		void bind() const { glBindTexture(GL_TEXTURE_2D, m_Texture); }
		static void activateUnit(int unit) { glActiveTexture(GL_TEXTURE0 + unit); }

	private:
		unsigned int m_Texture;
		Jade::Image m_Image;
	};
}