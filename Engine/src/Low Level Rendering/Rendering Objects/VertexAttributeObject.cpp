#include <GL/glew.h>
#include <vector>

#include "Low Level Rendering/Rendering Objects/VertexAttributeObject.h"

namespace Jade {
	// Only use if there is a single attribute pointer. For multiple pointers use addAttributePointers(). (UNTESTED)
	void VertexAttributeObject::addAttributePointer(VertexAttributePointer attributePointer) {
		bind();

		glVertexAttribPointer(
			0,
			attributePointer.size,
			attributePointer.type,
			GL_FALSE,
			attributePointer.sizeOfType * attributePointer.size,
			(void*)0
		);

		glEnableVertexAttribArray(0);

		m_VertexAttributePointers.push_back(attributePointer);
	}

	// If multiple attribute pointers are needed use this method.
	void VertexAttributeObject::addAttributePointers(std::vector<VertexAttributePointer> attributePointers) {
		m_VertexAttributePointers = std::move(attributePointers);

		int totalStride = 0;

		std::vector<VertexAttributePointer>::iterator it;
		for (it = m_VertexAttributePointers.begin(); it != m_VertexAttributePointers.end(); it++) {
			totalStride += (it->sizeOfType * it->size);
		}

		int count = 0;

		for (it = m_VertexAttributePointers.begin(); it != m_VertexAttributePointers.end(); it++) {
			int offset = 0;

			for (int i = 0; i <= count - 1; i++) {
				offset += (m_VertexAttributePointers.at(i).sizeOfType * m_VertexAttributePointers.at(i).size);
			}

			glVertexAttribPointer(
				count,
				it->size,
				it->type,
				GL_FALSE,
				totalStride,
				(void*)offset
			);

			glEnableVertexAttribArray(count);

			count++;
		}
	}

	VertexAttributePointer::VertexAttributePointer(unsigned int Size, GLenum Type) 
		: size(Size), type(Type) {
		switch (type) {
		default:
			sizeOfType = sizeof(float);
			LOGGER.log("Unreckognized type for Vertex attribute pointer.", Jade::WARNING);
			break;
		case GL_FLOAT:
			sizeOfType = sizeof(float);
			break;
		case GL_INT:
			sizeOfType = sizeof(int);
			break;
		case GL_UNSIGNED_INT:
			sizeOfType = sizeof(unsigned int);
			break;
		}
	}
}
