#pragma once

const float epsilon = 0.0001f;

const float pi = 3.1415926535897932385;

inline float degreesToRadians(float degrees) {
	return degrees * pi / 180.0;
}

inline bool compareFloats(float a, float b, float Epsilon = epsilon) {
	return fabs(a - b) < Epsilon;
}