#pragma once

#include "glm/glm.hpp"
#include "Low Level Rendering/Rendering Objects/Texture.h"

namespace Jade {
	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};

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

    struct TexturedMaterial {
        Texture diffuse;
        Texture specular;
        float shininess;
    };

    /*struct SpotLight { //TODO
        glm::vec3 position;
        glm::vec3 direction;
        float cutOff;
        float outerCutOff;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };*/
}