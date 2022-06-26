#pragma once
#include <cmath>
#include <iostream>

namespace Malachite {
	class Vector3f {
	public:
		float x;
		float y;
		float z;

		Vector3f() : x(0), y(0), z(0) {}
		Vector3f(float value) : x(value), y(value), z(value) {}
		Vector3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

		Vector3f operator-() const { return Vector3f(-x, -y, -z); }

		Vector3f& operator+=(const Vector3f& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3f& operator-=(const Vector3f& other) {
			*this += (-other);
			return *this;
		}

		Vector3f& operator*=(const float scaler) {
			x *= scaler;
			y *= scaler;
			z *= scaler;
			return *this;
		}

		Vector3f& operator/=(const float scaler) {
			return *this *= (1 / scaler);
		}

		bool operator==(const Vector3f& other) {
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const Vector3f& other) {
			return !operator==(other);
		}

		float lengthSquared() const {
			return x * x + y * y + z * z;
		}

		float length() const {
			return std::sqrt(lengthSquared());
		}

		void normalize() {
			*this /= this->length();
		}
	};

	inline std::ostream& operator<<(std::ostream& out, const Vector3f& vector) {
		return out << vector.x << ' ' << vector.y << ' ' << vector.z;
	}

	inline Vector3f operator+(const Vector3f& vector1, const Vector3f& vector2) {
		return Vector3f(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
	}

	inline Vector3f operator-(const Vector3f& vector1, const Vector3f& vector2) {
		return Vector3f(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
	}

	inline Vector3f operator*(const Vector3f& vector, const float scaler) {
		return Vector3f(vector.x * scaler, vector.y * scaler, vector.z * scaler);
	}

	inline Vector3f operator*(const float scaler, const Vector3f& vector) {
		return vector * scaler;
	}

	inline Vector3f operator/(const Vector3f& vector, const float scaler) {
		return vector * (1 / scaler);
	}

	inline float dot(const Vector3f& vector1, const Vector3f& vector2) {
		return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	}

	inline Vector3f cross(const Vector3f& vector1, const Vector3f& vector2) {
		return Vector3f(vector1.y * vector2.z - vector1.z * vector2.y, vector1.z * vector2.x - vector1.x * vector2.z, vector1.x * vector2.y - vector1.y * vector2.x);
	}
}