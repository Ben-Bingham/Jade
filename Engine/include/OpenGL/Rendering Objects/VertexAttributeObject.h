#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "Jade.h"

namespace Jade {
	namespace OpenGL {
		namespace RenderingObjects {
			struct VertexArrtibutePointer {
				VertexArrtibutePointer(unsigned int Size, GLenum Type)
					: size(Size), type(Type) {
					switch (type) {
					default:
						stride = sizeof(float) * size;
						LOGGER.log("Unreckognized type for Vertex attribute pointer.", Jade::WARNING);
						break;
					case GL_FLOAT:
						stride = sizeof(float) * size;
						break;
					case GL_INT:
						stride = sizeof(int) * size;
						break;
					case GL_UNSIGNED_INT:
						stride = sizeof(unsigned int) * size;
						break;
					}
				}

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