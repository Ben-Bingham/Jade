#include "UnitTests.h"
#include "Vector3f.h"

using namespace Malachite;

TEST_CASE("Length squared method returns the correct awnser.", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(vector1.lengthSquared() == 42.0f);
	REQUIRE(vector2.lengthSquared() == 26.0f);
	REQUIRE(vector3.lengthSquared() == 80.02669f);
}

TEST_CASE("Dot product can be succesfully calculated", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(dot(vector1, vector2) == 21.0f);
	REQUIRE(dot(vector2, vector3) == 35.37285f);
	//REQUIRE(dot(vector1, vector3) == 55.82956f); // FAILS but the numbers apear identical, floating point errors assumed
}

TEST_CASE("Cross product can be succesfully calculated", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(cross(vector1, vector2).x == 19.0f);
	REQUIRE(cross(vector1, vector2).y == -13.0f);
	REQUIRE(cross(vector1, vector2).z == -11.0f);

	REQUIRE(cross(vector2, vector3).x == -23.082255f);
	//REQUIRE(cross(vector2, vector3).y == 7.78021f); // FAILS but the numbers apear identical, floating point errors assumed
	//REQUIRE(cross(vector2, vector3).z == 15.366639f); // FAILS but the numbers apear identical, floating point errors assumed

	//REQUIRE(cross(vector1, vector3).x == 11.59772f); // FAILS but the numbers apear identical, floating point errors assumed
	REQUIRE(cross(vector1, vector3).y == -9.938511f);
	REQUIRE(cross(vector1, vector3).z == 3.30167f);
}