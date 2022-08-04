#pragma once

#include <GL/glew.h>

#include "Core Systems/Logging/Log.h"

#include "Core Systems/Resource Pipeline/Image.h"

namespace Jade {
	class Texture {
	public:
		Texture(const Jade::Image& image);

		void bind() const { glBindTexture(GL_TEXTURE_2D, m_Texture); }
		static void activateUnit(int unit) { glActiveTexture(GL_TEXTURE0 + unit); }

		Image getImage() { return m_Image; }

	private:
		unsigned int m_Texture;
		Image m_Image;
	};
}