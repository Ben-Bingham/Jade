#pragma once
#include <GL/glew.h>
#include <vector>

namespace Jade {
	class VertexBufferObject {
	public:
		void init(float vertices[], int length) {
			glGenBuffers(1, &m_VBO);

			bind();

			glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
		}

		VertexBufferObject(float vertices[], int length) { init(vertices, length); }
		VertexBufferObject(std::vector<float> vertices) {
			float* cVertices = new float[vertices.size() + 1];
			
			int i = 0;

			for each (float value in vertices) {
				cVertices[i] = value;
				i++;
			}

			init(cVertices, vertices.size());

			delete[] cVertices;
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
