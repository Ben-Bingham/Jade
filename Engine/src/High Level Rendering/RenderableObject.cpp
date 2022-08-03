#include <vector>

#include <glm/glm.hpp>

#include "High Level Rendering/Renderable Objects/RenderableObject.h"

namespace Jade {
    void RenderableObject::render(const PShader& shader) {
        additionalRendering(shader);

        calculateModelMatrix();
        shader.getProgram().setMatrix4f("model", m_ModelMatrix);
        
        m_VAO.bind();
        glDrawElements(GL_TRIANGLES, m_NumberOfIndicies, GL_UNSIGNED_INT, 0);
    }

    std::vector<Vertex> cubeVerticies = {
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f) },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f) },

        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f) },

        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f) },

        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f) },

        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f) },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f) },

        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f) }
    };

    std::vector<unsigned int> cubeIndicies = {
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

    std::vector<Vertex> pyramidVerticies = {
        Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.44721f, 0.89443f),  glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(0.0f, 0.44721f, 0.89443f),  glm::vec2(0.5f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.44721f, 0.89443f),  glm::vec2(1.0f, 0.0f)},

        Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.89443f, 0.44721f, 0.0f),  glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(0.89443f, 0.44721f, 0.0f),  glm::vec2(0.5f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.89443f, 0.44721f, 0.0f),  glm::vec2(1.0f, 0.0f)},

        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.44721f, -0.89443f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.44721f, -0.89443f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(0.0f, 0.44721f, -0.89443f), glm::vec2(0.5f, 1.0f)},

        Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-0.89443f, 0.44721f, 0.0f),  glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.89443f, 0.44721f, 0.0f),  glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(-0.89443f, 0.44721f, 0.0f),  glm::vec2(0.5f, 1.0f)},

        Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f),         glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f),         glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),         glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f, 0.0f),         glm::vec2(1.0f, 0.0f)}
    };

    std::vector<unsigned int> pyramidIndicies = {
        0,  1,  2,
        3,  4,  5,
        6,  7,  8,
        9, 10, 11,
        12, 13, 14,
        13, 15, 14
    };

    Mesh RenderableObject::cubeMesh = Mesh(cubeVerticies, cubeIndicies, 0);

    Mesh RenderableObject::pyramidMesh = Mesh(pyramidVerticies, pyramidIndicies, 0);
}