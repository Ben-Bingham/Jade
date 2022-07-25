#pragma once

#include "Low Level Rendering/Shaders/ShaderStructs.h"
#include "High Level Rendering/Material.h"

namespace Jade {
	class MaterialCreator {
	public:
		static Material DefaultMaterial() {
			return Material(makeTextureFromColour(Colour(0, 66, 42)), makeTextureFromColour(Colour(255, 255, 255)), 32.0f);
		}

	private:
		static unsigned int getNextProceduralID() { proceduralImageID++; return proceduralImageID; }

		static Texture makeTextureFromColour(Colour colour) {
			return Texture(Image("assets\\procedural\\procedural_texture_" + std::to_string(getNextProceduralID()), Colour(colour), 1, 1));
		}

		static unsigned int proceduralImageID;
	};
}