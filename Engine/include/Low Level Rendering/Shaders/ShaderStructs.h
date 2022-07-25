#pragma once

#include "glm/glm.hpp"
#include "Low Level Rendering/Rendering Objects/Texture.h"

namespace Jade {
    struct DirectionalLight {
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct PointLight {
        glm::vec3 position;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
}