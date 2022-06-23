#include "UnitTests.h"
#include "Vector3f.h"

using namespace Malachite;

TEST_CASE("Length squared method returns the correct awnser.", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(vector1.lengthSquared() == 42.0f);
	REQUIRE(vector2.lengthSquared() == 26.0f);
	REQUIRE(vector3.lengthSquared() == 8.94576f);
}

TEST_CASE("Dot product can be succesfully calculated", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(dot(vector1, vector2) == 21.0f);
	REQUIRE(dot(vector2, vector3) == 35.3728f);
	REQUIRE(dot(vector1, vector3) == 55.8296f);
}

TEST_CASE("Cross product can be succesfully calculated", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(cross(vector1, vector2) == Vector3f(19.0f, -13.0f, -11.0f));
	REQUIRE(cross(vector2, vector3) == Vector3f(-23.082255f, 7.780209f, 15.366639f));
	REQUIRE(cross(vector1, vector3) == Vector3f(11.597721f, -9.938511f, 3.301671f));
}