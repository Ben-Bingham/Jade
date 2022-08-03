#pragma once

#include <glm/glm.hpp>
#include <assimp/types.h>

namespace Jade {
	class Colour {
	public:
		Colour() : colour(0.0f, 0.0f, 0.0f, 1.0f) {}
		Colour(float value) : colour(value, value, value, value) {}
		Colour(glm::vec4 colour) : colour(colour) {}
		explicit Colour(float r, float g, float b, float a = 1.0f) : colour(r, g, b, a) {}
		explicit Colour(int r, int g, int b, int a = 255) : colour(initWith0to255(r, g, b, a)) {}
		Colour(aiColor3D colour) : colour(colour.r, colour.g, colour.b, 1.0) {}
		Colour(aiColor4D colour) : colour(colour.r, colour.g, colour.b, colour.a) {}

		glm::vec4 colour;

		glm::vec3 toVec3() const { return glm::vec3(colour.x, colour.y, colour.z); }

		bool operator==(const Colour& other) const {
			return colour == other.colour;
		}

		bool operator!=(const Colour& other) const {
			return !operator==(other);
		}

	private:
		glm::vec4 initWith0to255(int r, int g, int b, int a) {
			float oneOverTwoFifyFive = 1.0f / 255.0f;
			float x, y, z, w;
			if (r != 255) {
				x = (float)(oneOverTwoFifyFive * (float)(r % 255));
			}
			else {
				x = 1.0f;
			}

			if (g != 255) {
				y = (float)(oneOverTwoFifyFive * (float)(g % 255));
			}
			else {
				y = 1.0f;
			}

			if (b != 255) {
				z = (float)(oneOverTwoFifyFive * (float)(b % 255));
			}
			else {
				z = 1.0f;
			}

			if (a != 255) {
				w = (float)(oneOverTwoFifyFive * (float)(a % 255));
			}
			else {
				w = 1.0f;
			}

			return glm::vec4(x, y, z, w);
		}
	};
}