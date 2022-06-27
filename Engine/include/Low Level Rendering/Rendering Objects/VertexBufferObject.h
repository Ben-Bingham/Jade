#pragma once
#include <GL/glew.h>

namespace Jade {
	class VertexBufferObject {
	public:
		VertexBufferObject(float vertices[], int length) {
			glGenBuffers(1, &m_VBO);
		
			bind();

			glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
		}

		~VertexBufferObject() {
			glDeleteBuffers(1, &m_VBO);
		}

		void bind() const{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		}

		static void unbind() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	private:
		unsigned int m_VBO;
	};
}
