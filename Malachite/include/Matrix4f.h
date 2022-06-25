#pragma once
#include "Vector3f.h"
#include "Vector4f.h"

namespace Malachite {
	class Matrix4f {
	public:
		float m[4][4]; // m[row][collum]

		Matrix4f() {
			m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
			m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
			m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}
	};

	inline Vector4f& operator*(const Vector4f& vector4, const Matrix4f& matrix) {
		Vector4f result;
		result.x = (matrix.m[0][0] * vector4.x) + (matrix.m[0][1] * vector4.y) + (matrix.m[0][2] * vector4.z) + (matrix.m[0][3] * vector4.w);
		result.y = (matrix.m[1][0] * vector4.x) + (matrix.m[1][1] * vector4.y) + (matrix.m[1][2] * vector4.z) + (matrix.m[1][3] * vector4.w);
		result.z = (matrix.m[2][0] * vector4.x) + (matrix.m[2][1] * vector4.y) + (matrix.m[2][2] * vector4.z) + (matrix.m[2][3] * vector4.w);
		result.w = (matrix.m[3][0] * vector4.x) + (matrix.m[3][1] * vector4.y) + (matrix.m[3][2] * vector4.z) + (matrix.m[3][3] * vector4.w);
		return result;
	}

	inline Vector3f& operator*(const Vector3f& vector3, const Matrix4f& matrix) {
		Vector4f vector4(vector3, 1);
		Vector4f result = (vector4 * matrix);
		return Vector3f(result.x, result.y, result.z);
	}
}