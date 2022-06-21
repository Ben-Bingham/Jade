#define CATCH_CONFIG_MAIN
#include "catch.h"

int add(const int a, const int b) {
	return a + b;
}

TEST_CASE("Math did not break") {
	REQUIRE(add(1, 1) == 2);
}