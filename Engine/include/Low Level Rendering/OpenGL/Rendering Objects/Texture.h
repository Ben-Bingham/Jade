#pragma once

#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Image.h"

namespace Jade {
	namespace OpenGL {
		namespace RenderingObjects {
			class Texture {
			public:
				Texture(Jade::Resources::Image image);
				Texture(std::string& path);
				Texture(std::string&& path);

				void bind() { glBindTexture(GL_TEXTURE_2D, m_Texture); }

			private:
				unsigned int m_Texture;
				Jade::Resources::Image m_Image;
			};
		}
	}
}