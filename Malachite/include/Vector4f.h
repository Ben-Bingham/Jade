#pragma once
#include "Vector3f.h"

namespace Malachite {
	class Vector4f {
	public:
		float x;
		float y;
		float z;
		float w;

		Vector4f() : x(0), y(0), z(0), w(0) {}
		Vector4f(float value) : x(value), y(value), z(value), w(value) {}
		Vector4f(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}
		Vector4f(const Vector3f& vector3, float W) : x(vector3.x), y(vector3.y), z(vector3.z), w(W) {}
	};

	using Quaternion = Vector4f;
}