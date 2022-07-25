#pragma once

#include "Low Level Rendering/Rendering Objects/Texture.h"
#include "Core Systems/Resource Pipeline/Model.h"

namespace Jade {
	struct Material {
		Material(const AssimpMaterial& material)
			: diffuse(Texture(material.diffuse)), specular(Texture(material.specular)), shininess(material.shininess) {
		}

		Material(const Texture& Diffuse, const Texture& Specular, const float Shininess)
			: diffuse(Diffuse), specular(Specular), shininess(Shininess) {

		}

		Texture diffuse;
		Texture specular;
		float shininess;
	};
}