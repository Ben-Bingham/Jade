#pragma once
#include "Light.h"
#include "High Level Rendering/Colour.h"

namespace Jade {
	class PointLight : public Light {
	public:
		PointLight(
			Colour Ambient = Colour{0.2f},
			Colour Diffuse = Colour{0.5f},
			Colour Specular = Colour{1.0f},
			float Constant = 1.0f,
			float Linear = 0.09,
			float Quadratic = 0.032
		) : constant(Constant), linear(Linear), quadratic(Quadratic), ambient(Ambient), diffuse(Diffuse), specular(Specular) { }

		float constant{};
		float linear{};
		float quadratic{};

		Colour ambient{};
		Colour diffuse{};
		Colour specular{};

	private:
	};
}