#include "UnitTests.h"
#include "Vector3f.h"
#include "Quaternion.h"
#include "Malachite.h"

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

	REQUIRE(compareFloats(dot(vector1, vector2), 21.0f));
	REQUIRE(compareFloats(dot(vector2, vector3), 35.37285f));
	REQUIRE(compareFloats(dot(vector1, vector3), 55.82956f));
}

TEST_CASE("Cross product can be succesfully calculated", "[Vector3f]") {
	Vector3f vector1(4, 5, 1);
	Vector3f vector2(3, 1, 4);
	Vector3f vector3(4.687413f, 6.684684f, 3.656481f);

	REQUIRE(compareFloats(cross(vector1, vector2).x, 19.0f));
	REQUIRE(compareFloats(cross(vector1, vector2).y, -13.0f));
	REQUIRE(compareFloats(cross(vector1, vector2).z, -11.0f));

	REQUIRE(compareFloats(cross(vector2, vector3).x, -23.082255f));
	REQUIRE(compareFloats(cross(vector2, vector3).y, 7.78021f)); 
	REQUIRE(compareFloats(cross(vector2, vector3).z, 15.366639f));

	REQUIRE(compareFloats(cross(vector1, vector3).x, 11.59772f));
	REQUIRE(compareFloats(cross(vector1, vector3).y, -9.938511f));
	REQUIRE(compareFloats(cross(vector1, vector3).z, 3.30167f));
}

// QUATERNIONS

TEST_CASE("Quaternion can be created using angle and axis", "[Quaternion]") {
	Quaternion quaternion(90, Vector3f(0, 1, 0));

	REQUIRE(compareFloats(quaternion.i, 0));
	REQUIRE(compareFloats(quaternion.j, 0.8509f));
	REQUIRE(compareFloats(quaternion.k, 0));
	REQUIRE(compareFloats(quaternion.s, 0.5253f));

	Quaternion quaternion2(90, Vector3f(0, 1, 1));

	REQUIRE(compareFloats(quaternion2.i, 0));
	REQUIRE(compareFloats(quaternion2.j, 0.6016797f));
	REQUIRE(compareFloats(quaternion2.k, 0.6016797f));
	REQUIRE(compareFloats(quaternion2.s, 0.525322f));

	Quaternion quaternion3(134.13556f, Vector3f(12.548f, 0.1234515f, 5.154156f));

	REQUIRE(compareFloats(quaternion3.i, -0.8219481f));
	REQUIRE(compareFloats(quaternion3.j, -0.0080866f));
	REQUIRE(compareFloats(quaternion3.k, -0.3376195f));
	REQUIRE(compareFloats(quaternion3.s, -0.4586382f));
}