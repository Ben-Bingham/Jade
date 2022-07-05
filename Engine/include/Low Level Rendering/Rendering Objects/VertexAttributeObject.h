#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "Jade.h"

namespace Jade {
	enum AttributeNames {
		POSITION,
		NORMAL,
		TEXTURE_CORDINATE
	};

	struct VertexAttributePointer {
		VertexAttributePointer(unsigned int Size, GLenum Type, AttributeNames name);

		unsigned int size;
		GLenum type;
		unsigned int sizeOfType;
		AttributeNames name;
	};

	class VertexAttributeObject {
	public:
		VertexAttributeObject() {
			glGenVertexArrays(1, &m_VAO);

			bind();
		}

		VertexAttributeObject(const VertexAttributeObject&) = default;
		VertexAttributeObject(VertexAttributeObject&&) = default;
		VertexAttributeObject& operator=(const VertexAttributeObject&) = default;
		VertexAttributeObject& operator=(VertexAttributeObject&&) = default;

		void dispose() {
			glDeleteVertexArrays(1, &m_VAO);
		}

		void bind() const {
			glBindVertexArray(m_VAO);
		}

		static void unbind() {
			glBindVertexArray(0);
		}

		void setAttributePointer(VertexAttributePointer attributePointer);
		void addAttributePointers(std::vector<VertexAttributePointer> attributePointers);

	private:
		unsigned int m_VAO;
		std::vector<VertexAttributePointer> m_VertexAttributePointers;
	};
}