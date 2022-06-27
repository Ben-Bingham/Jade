#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "Jade.h"

namespace Jade {
	struct VertexAttributePointer {
		VertexAttributePointer(unsigned int Size, GLenum Type);

		unsigned int size;
		GLenum type;
		unsigned int sizeOfType;
	};

	class VertexAttributeObject {
	public:
		VertexAttributeObject() {
			glGenVertexArrays(1, &m_VAO);

			bind();
		}

		~VertexAttributeObject() {
			bind();
			glDeleteVertexArrays(1, &m_VAO);
		}

		void bind() const {
			glBindVertexArray(m_VAO);
		}

		static void unbind() {
			glBindVertexArray(0);
		}

		void addAttributePointer(VertexAttributePointer attributePointer);
		void addAttributePointers(std::vector<VertexAttributePointer> attributePointers);

	private:
		unsigned int m_VAO;
		std::vector<VertexAttributePointer> m_VertexAttributePointers;
	};
}