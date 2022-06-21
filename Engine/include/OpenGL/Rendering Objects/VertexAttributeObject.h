#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "Jade.h"

namespace Jade {
	namespace OpenGL {
		namespace RenderingObjects {
			struct VertexArrtibutePointer {
				VertexArrtibutePointer(unsigned int Size, GLenum Type);

				unsigned int size;
				GLenum type;
				unsigned int stride;
			};

			class VertexAttributeObject {
			public:
				VertexAttributeObject() {
					glGenVertexArrays(1, &m_VAO);

					bind();
				}

				~VertexAttributeObject() {
					glDeleteVertexArrays(1, &m_VAO);
				}

				void bind() const {
					glBindVertexArray(m_VAO);
				}

				static void unbind() {
					glBindVertexArray(0);
				}

				unsigned int getVAO() const { return m_VAO; }

				void addAttributePointer(VertexArrtibutePointer attributePointer);

			private:
				unsigned int m_VAO;
				std::vector<VertexArrtibutePointer> m_VertexArrtibutePointers;
			};
		}
	}
}