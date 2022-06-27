#pragma once
#include <GL/glew.h>

namespace Jade {

	class ElementBufferObject {
	public:
		ElementBufferObject(unsigned int indices[], int length) {
			glGenBuffers(1, &m_EBO);

			bind();

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, indices, GL_STATIC_DRAW);
		}

		~ElementBufferObject() {
			glDeleteBuffers(1, &m_EBO);
		}

		void bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		}

		static void unbind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	private:
		unsigned int m_EBO;
	};

}