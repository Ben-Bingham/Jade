#include "Core Systems/Logging/Log.h"
#include "UnitTests.h"
#include "Core Systems/Resource Pipeline/TextFile.h"

TEST_CASE("TextFile class can read text files", "[TextFile]") {

	Jade::Resources::TextFile file("assets\\Test Text Document.txt");

	std::string string = "This is a test document.\n\nIt has multiple lines.\n\nIt is quite short.\0";

	REQUIRE(file.getContent() == string);
}

TEST_CASE("TextFile class can read empty text files", "[TextFile]") {

	Jade::Resources::TextFile file("assets\\Test Text Document2.txt");

	std::string string = "\0";

	REQUIRE(file.getContent() == string);
}