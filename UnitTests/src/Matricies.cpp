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

TEST_CASE("Matrix can multiply another matrix", "[Matrix4f]") {
	Vector4f row1(5, 7, 9, 10);
	Vector4f row2(2, 3, 3, 8);
	Vector4f row3(8, 10, 2, 3);
	Vector4f row4(3, 3, 4, 8);

	Matrix4f matrix1(row1, row2, row3, row4);

	Vector4f row1_2(3, 10, 12, 18);
	Vector4f row2_2(12, 1, 4, 9);
	Vector4f row3_2(9, 10, 12, 2);
	Vector4f row4_2(3, 12, 4, 10);

	Matrix4f matrix2(row1_2, row2_2, row3_2, row4_2);

	Matrix4f result = matrix1 * matrix2;

	REQUIRE(result.m[0][0] == 210);
	REQUIRE(result.m[0][1] == 267);
	REQUIRE(result.m[0][2] == 236);
	REQUIRE(result.m[0][3] == 271);

	REQUIRE(result.m[1][0] == 93);
	REQUIRE(result.m[1][1] == 149);
	REQUIRE(result.m[1][2] == 104);
	REQUIRE(result.m[1][3] == 149);

	REQUIRE(result.m[2][0] == 171);
	REQUIRE(result.m[2][1] == 146);
	REQUIRE(result.m[2][2] == 172);
	REQUIRE(result.m[2][3] == 268);

	REQUIRE(result.m[3][0] == 105);
	REQUIRE(result.m[3][1] == 169);
	REQUIRE(result.m[3][2] == 128);
	REQUIRE(result.m[3][3] == 169);

}

TEST_CASE("Matrix can scale a vector", "[Matrix4f]") {
	Matrix4f matrix;
	matrix.scale(Vector3f(2));
	Vector3f vector(1, 2, 3);

	Vector3f result = vector * matrix;
	REQUIRE(result.x == 2);
	REQUIRE(result.y == 4);
	REQUIRE(result.z == 6);
}

TEST_CASE("Matrix can translate a vector", "[Matrix4f]") {

}

TEST_CASE("Matrix can rotate a vector", "[Matrix4f]") {

}

TEST_CASE("Two matricies can be multiplied together", "[Matrix4f]") {

}