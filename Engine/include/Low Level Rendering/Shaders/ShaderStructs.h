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
}