#pragma once
#include <GL/glew.h>
#include <vector>

namespace Jade {
	class ElementBufferObject {
	public:
		ElementBufferObject(unsigned int indices[], int length) { init(indices, length); }
		ElementBufferObject(std::vector<unsigned int> indices) { 
			unsigned int* cIndices = new unsigned int[indices.size() + 1];

			int i = 0;

			for each (unsigned int value in indices) {
				cIndices[i] = value;
				i++;
			}

			init(cIndices, (int)(indices.size() * sizeof(unsigned int)));

			delete[] cIndices;
		}

		void init(unsigned int indices[], int length) {
			glGenBuffers(1, &m_EBO);

			bind();

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, indices, GL_STATIC_DRAW);
		}

		void bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		}

		static void unbind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void dispose() {
			glDeleteBuffers(1, &m_EBO);
		}

	private:
		unsigned int m_EBO;
	};
}