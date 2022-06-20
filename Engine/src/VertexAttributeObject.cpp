#include <GL/glew.h>
#include <vector>
#include "VertexAttributeObject.h"

void VertexAttributeObject::addAttributePointer(VertexArrtibutePointer attributePointer) {
	unsigned int offset = 0;
	for (int i = 0; i < m_VertexArrtibutePointers.size(); i++) {
		offset += m_VertexArrtibutePointers.at(i).stride;
	}

	glVertexAttribPointer(
		m_VertexArrtibutePointers.size(),
		attributePointer.size,
		attributePointer.type,
		GL_FALSE,
		attributePointer.size * sizeof(float),
		(void*)offset
	);

	glEnableVertexAttribArray(m_VertexArrtibutePointers.size());

	m_VertexArrtibutePointers.push_back(attributePointer);
}