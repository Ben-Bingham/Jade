#pragma once
#include <GL/glew.h>
#include <vector>

namespace Jade {
	class VertexBufferObject {
	public:
		VertexBufferObject(float vertices[], int length) { init(vertices, length); }
		VertexBufferObject(const std::vector<float>& vertices) {
			float* cVertices = new float[vertices.size() + 1];
			
			int i = 0;

			for each (float value in vertices) {
				cVertices[i] = value;
				i++;
			}

			init(cVertices, (int)(vertices.size() * sizeof(float)));

			delete[] cVertices;
		}

		void init(float vertices[], int length) {
			glGenBuffers(1, &m_VBO);

			bind();

			glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
		}

		void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		}

		static void unbind() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void dispose() {
			glDeleteBuffers(1, &m_VBO);
		}

	private:
		unsigned int m_VBO;
	};
}
