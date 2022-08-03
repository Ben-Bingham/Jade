#pragma once
#include "Entity Component System/Gameobjects/Gameobject.h"

namespace Jade {
	class PShader;

	class Light : public Gameobject {
	public:
		Light() {}

		virtual ~Light() = 0;
	};
}