#include <vector>

#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
    void RenderableObject::render(const RenderingRuleSet& ruleSet) const {
        additionalRendering(ruleSet);

        ruleSet.getProgram().setMatrix4f("model", m_Transform.getMatrix());

        m_VAO.bind();

        glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerticies);
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
