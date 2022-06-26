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

		Matrix4f(const Vector4f& row1, const Vector4f& row2, const Vector4f& row3, const Vector4f& row4) {
			m[0][0] = row1.x; m[0][1] = row1.y; m[0][2] = row1.z; m[0][3] = row1.w;
			m[1][0] = row2.x; m[1][1] = row2.y; m[1][2] = row2.z; m[1][3] = row2.w;
			m[2][0] = row3.x; m[2][1] = row3.y; m[2][2] = row3.z; m[2][3] = row3.w;
			m[3][0] = row4.x; m[3][1] = row4.y; m[3][2] = row4.z; m[3][3] = row4.w;
		}

		void scale(const Vector3f& scaleVector) {
			Matrix4f scaleMatrix;
			scaleMatrix.m[0][0] = scaleVector.x;
			scaleMatrix.m[1][1] = scaleVector.y;
			scaleMatrix.m[2][2] = scaleVector.z;
			*this *= scaleMatrix;
		}

		Matrix4f& operator*=(const Matrix4f& other) {
			m[0][0] = (m[0][0] * other.m[0][0]) + (m[0][1] * other.m[1][0]) + (m[0][2] * other.m[2][0]) + (m[0][3] * other.m[3][0]);
			m[0][1] = (m[0][0] * other.m[0][1]) + (m[0][1] * other.m[1][1]) + (m[0][2] * other.m[2][1]) + (m[0][3] * other.m[3][1]);
			m[0][2] = (m[0][0] * other.m[0][2]) + (m[0][1] * other.m[1][2]) + (m[0][2] * other.m[2][2]) + (m[0][3] * other.m[3][2]);
			m[0][3] = (m[0][0] * other.m[0][3]) + (m[0][1] * other.m[1][3]) + (m[0][2] * other.m[2][3]) + (m[0][3] * other.m[3][3]);

			// Second row
			m[1][0] = (m[1][0] * other.m[0][0]) + (m[1][1] * other.m[1][0]) + (m[1][2] * other.m[2][0]) + (m[1][3] * other.m[3][0]);
			m[1][1] = (m[1][0] * other.m[0][1]) + (m[1][1] * other.m[1][1]) + (m[1][2] * other.m[2][1]) + (m[1][3] * other.m[3][1]);
			m[1][2] = (m[1][0] * other.m[0][2]) + (m[1][1] * other.m[1][2]) + (m[1][2] * other.m[2][2]) + (m[1][3] * other.m[3][2]);
			m[1][3] = (m[1][0] * other.m[0][3]) + (m[1][1] * other.m[1][3]) + (m[1][2] * other.m[2][3]) + (m[1][3] * other.m[3][3]);
								 
			// Third row		 
			m[2][0] = (m[2][0] * other.m[0][0]) + (m[2][1] * other.m[1][0]) + (m[2][2] * other.m[2][0]) + (m[2][3] * other.m[3][0]);
			m[2][1] = (m[2][0] * other.m[0][1]) + (m[2][1] * other.m[1][1]) + (m[2][2] * other.m[2][1]) + (m[2][3] * other.m[3][1]);
			m[2][2] = (m[2][0] * other.m[0][2]) + (m[2][1] * other.m[1][2]) + (m[2][2] * other.m[2][2]) + (m[2][3] * other.m[3][2]);
			m[2][3] = (m[2][0] * other.m[0][3]) + (m[2][1] * other.m[1][3]) + (m[2][2] * other.m[2][3]) + (m[2][3] * other.m[3][3]);
						
			// Fourth row
			m[3][0] = (m[3][0] * other.m[0][0]) + (m[3][1] * other.m[1][0]) + (m[3][2] * other.m[2][0]) + (m[3][3] * other.m[3][0]);
			m[3][1] = (m[3][0] * other.m[0][1]) + (m[3][1] * other.m[1][1]) + (m[3][2] * other.m[2][1]) + (m[3][3] * other.m[3][1]);
			m[3][2] = (m[3][0] * other.m[0][2]) + (m[3][1] * other.m[1][2]) + (m[3][2] * other.m[2][2]) + (m[3][3] * other.m[3][2]);
			m[3][3] = (m[3][0] * other.m[0][3]) + (m[3][1] * other.m[1][3]) + (m[3][2] * other.m[2][3]) + (m[3][3] * other.m[3][3]);
			return *this;
		}
	};

	inline Matrix4f operator*(const Matrix4f& matrix1, const Matrix4f& matrix2) {
		Matrix4f result;
		// First row
		result.m[0][0] = (matrix1.m[0][0] * matrix2.m[0][0]) + (matrix1.m[0][1] * matrix2.m[1][0]) + (matrix1.m[0][2] * matrix2.m[2][0]) + (matrix1.m[0][3] * matrix2.m[3][0]);
		result.m[0][1] = (matrix1.m[0][0] * matrix2.m[0][1]) + (matrix1.m[0][1] * matrix2.m[1][1]) + (matrix1.m[0][2] * matrix2.m[2][1]) + (matrix1.m[0][3] * matrix2.m[3][1]);
		result.m[0][2] = (matrix1.m[0][0] * matrix2.m[0][2]) + (matrix1.m[0][1] * matrix2.m[1][2]) + (matrix1.m[0][2] * matrix2.m[2][2]) + (matrix1.m[0][3] * matrix2.m[3][2]);
		result.m[0][3] = (matrix1.m[0][0] * matrix2.m[0][3]) + (matrix1.m[0][1] * matrix2.m[1][3]) + (matrix1.m[0][2] * matrix2.m[2][3]) + (matrix1.m[0][3] * matrix2.m[3][3]);

		// Second row
		result.m[1][0] = (matrix1.m[1][0] * matrix2.m[0][0]) + (matrix1.m[1][1] * matrix2.m[1][0]) + (matrix1.m[1][2] * matrix2.m[2][0]) + (matrix1.m[1][3] * matrix2.m[3][0]);
		result.m[1][1] = (matrix1.m[1][0] * matrix2.m[0][1]) + (matrix1.m[1][1] * matrix2.m[1][1]) + (matrix1.m[1][2] * matrix2.m[2][1]) + (matrix1.m[1][3] * matrix2.m[3][1]);
		result.m[1][2] = (matrix1.m[1][0] * matrix2.m[0][2]) + (matrix1.m[1][1] * matrix2.m[1][2]) + (matrix1.m[1][2] * matrix2.m[2][2]) + (matrix1.m[1][3] * matrix2.m[3][2]);
		result.m[1][3] = (matrix1.m[1][0] * matrix2.m[0][3]) + (matrix1.m[1][1] * matrix2.m[1][3]) + (matrix1.m[1][2] * matrix2.m[2][3]) + (matrix1.m[1][3] * matrix2.m[3][3]);

		// Third row
		result.m[2][0] = (matrix1.m[2][0] * matrix2.m[0][0]) + (matrix1.m[2][1] * matrix2.m[1][0]) + (matrix1.m[2][2] * matrix2.m[2][0]) + (matrix1.m[2][3] * matrix2.m[3][0]);
		result.m[2][1] = (matrix1.m[2][0] * matrix2.m[0][1]) + (matrix1.m[2][1] * matrix2.m[1][1]) + (matrix1.m[2][2] * matrix2.m[2][1]) + (matrix1.m[2][3] * matrix2.m[3][1]);
		result.m[2][2] = (matrix1.m[2][0] * matrix2.m[0][2]) + (matrix1.m[2][1] * matrix2.m[1][2]) + (matrix1.m[2][2] * matrix2.m[2][2]) + (matrix1.m[2][3] * matrix2.m[3][2]);
		result.m[2][3] = (matrix1.m[2][0] * matrix2.m[0][3]) + (matrix1.m[2][1] * matrix2.m[1][3]) + (matrix1.m[2][2] * matrix2.m[2][3]) + (matrix1.m[2][3] * matrix2.m[3][3]);

		// Fourth row
		result.m[3][0] = (matrix1.m[3][0] * matrix2.m[0][0]) + (matrix1.m[3][1] * matrix2.m[1][0]) + (matrix1.m[3][2] * matrix2.m[2][0]) + (matrix1.m[3][3] * matrix2.m[3][0]);
		result.m[3][1] = (matrix1.m[3][0] * matrix2.m[0][1]) + (matrix1.m[3][1] * matrix2.m[1][1]) + (matrix1.m[3][2] * matrix2.m[2][1]) + (matrix1.m[3][3] * matrix2.m[3][1]);
		result.m[3][2] = (matrix1.m[3][0] * matrix2.m[0][2]) + (matrix1.m[3][1] * matrix2.m[1][2]) + (matrix1.m[3][2] * matrix2.m[2][2]) + (matrix1.m[3][3] * matrix2.m[3][2]);
		result.m[3][3] = (matrix1.m[3][0] * matrix2.m[0][3]) + (matrix1.m[3][1] * matrix2.m[1][3]) + (matrix1.m[3][2] * matrix2.m[2][3]) + (matrix1.m[3][3] * matrix2.m[3][3]);
		return result;
	}

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