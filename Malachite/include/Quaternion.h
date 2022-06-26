#pragma once
#include "Vector3f.h"

namespace Malachite {
	class Quaternion {
	public:
		float i;
		float j;
		float k;
		float s;
		Quaternion() : i(0), j(0), k(0), s(0) {}
		Quaternion(float I, float J, float K, float S) : i(I), j(J), k(K), s(S) {}

		Quaternion(float angle, Vector3f axis) {
			axis.normalize();
			s = cos(angle / 2);
			i = sin(angle / 2) * axis.x;
			j = sin(angle / 2) * axis.y;
			k = sin(angle / 2) * axis.z;
		}
	};
}