#include "UnitTests.h"
#include "Matrix4f.h"

using namespace Malachite;

TEST_CASE("Blank matrix does not modifiy a vector", "[Matrix4f]") {
	Matrix4f matrix;
	Vector3f vector(1, 2, 3);

	Vector3f result = vector * matrix;
	REQUIRE(result.x == vector.x);
	REQUIRE(result.y == vector.y);
	REQUIRE(result.z == vector.z);
}

TEST_CASE("Matrix can scale a vector", "[Matrix4f]") {

}

TEST_CASE("Matrix can translate a vector", "[Matrix4f]") {

}

TEST_CASE("Matrix can rotate a vector", "[Matrix4f]") {

}

TEST_CASE("Two matricies can be multiplied together", "[Matrix4f]") {

}