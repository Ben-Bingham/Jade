#include <vector>

#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
	/*void RenderableObject::render(const RenderingRuleSet& ruleSet) const {
		if (ruleSet.ruleSet == SOLID_COLOUR) {
			ruleSet.getProgram().setVector4f("objectColour", m_ObjectColour);
		}
        else if (ruleSet.ruleSet == TEXTURE) {
            ruleSet.getProgram().setMaterial("material", m_Material);
        }
		else {
			ruleSet.getProgram().setMaterial("material", m_Material);
		}

        getTexture().bind();
        Texture::activateUnit(0);

		ruleSet.getProgram().setMatrix4f("model", m_Transform.getMatrix());

		m_VAO.bind();
		
		glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerticies);
	}*/

	std::vector<float> RenderableObject::cubeVerticies = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	std::vector<float> RenderableObject::pyramidVerticies = {
		-0.5f, -0.5f,  0.5f,   0.0f, 0.44721f, 0.89443f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.44721f, 0.89443f,   1.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,   0.0f, 0.44721f, 0.89443f,   0.5f, 1.0f,
                              
		 0.5f, -0.5f,  0.5f,   0.89443f, 0.44721f, 0.0f,   0.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,   0.89443f, 0.44721f, 0.0f,   0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.89443f, 0.44721f, 0.0f,   1.0f, 0.0f,
                              
		-0.5f, -0.5f, -0.5f,   0.0f, 0.44721f, -0.89443f,  1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 0.44721f, -0.89443f,  0.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,   0.0f, 0.44721f, -0.89443f,  0.5f, 1.0f,
                              
		-0.5f, -0.5f,  0.5f,  -0.89443f, 0.44721f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -0.89443f, 0.44721f, 0.0f,   0.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,  -0.89443f, 0.44721f, 0.0f,   0.5f, 1.0f,
                              
		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,          0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,          1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,          0.0f, 0.0f,
                              
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,          1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,          1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,          0.0f, 0.0f, 
	};
}