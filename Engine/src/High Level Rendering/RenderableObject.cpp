#include <vector>

#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
    void RenderableObject::render(const RenderingRuleSet& ruleSet) const {
        additionalRendering(ruleSet);

        ruleSet.getProgram().setMatrix4f("model", m_Transform.getMatrix());

        m_VAO.bind();

        glDrawElements(GL_TRIANGLES, m_NumberOfIndicies, GL_UNSIGNED_INT, 0);
    }

    std::vector<float> RenderableObject::cubeVerticies = {
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,

         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,                         
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,             

        -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,                               
        -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,                                       
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,              

         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,                                            
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,             

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,                                   
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
    };

    std::vector<unsigned int> RenderableObject::cubeIndicies = {
         0,  1,  2,
         1,  3,  2,
         4,  5,  6,
         5,  7,  6,
         8,  9, 10,
         9, 11, 10,
        12, 13, 14,
        13, 15, 14,
        16, 17, 18,
        17, 19, 18,
        20, 21, 22,
        21, 23, 22,
    };

	std::vector<float> RenderableObject::pyramidVerticies = {
		-0.5f, -0.5f,  0.5f,   0.0f, 0.44721f, 0.89443f,   0.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,   0.0f, 0.44721f, 0.89443f,   0.5f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.44721f, 0.89443f,   1.0f, 0.0f,
                              
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
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,          1.0f, 0.0f,
	};

    std::vector<unsigned int> RenderableObject::pyramidIndicies = {
        0,  1,  2,
        3,  4,  5,
        6,  7,  8,
        9, 10, 11,
        12, 13, 14,
        13, 15, 14
    };
}
