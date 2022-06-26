#include "Core Systems/Logging/Log.h"
#include "UnitTests.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Core Systems/Resource Pipeline/Image.h"

// Text files -------------------------------------------------------------------------------------
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

TEST_CASE("TextFile class can save path of file", "[TextFile]") {
	std::string path = "assets\\Test Text Document2.txt";
	Jade::Resources::TextFile file(path);

	REQUIRE(file.getPath() == path);
}


// Images -----------------------------------------------------------------------------------------
TEST_CASE("Image class can read Max alpha png images", "[Image]") {
	unsigned char requiredData[] = {
		255, 0  , 0  , 255,
		255, 255, 0  , 255,
		0  , 255, 0  , 255,
		255, 0  , 255, 255,
		255, 255, 255, 255,
		0  , 255, 255, 255,
		0  , 0  , 0  , 255,
		255, 0  , 255, 255,
		0  , 0  , 255, 255
	};

	Jade::Resources::Image image("assets\\pngTest.png", false);

	for (int i = 0; i < 36; i++) {
		REQUIRE(image.getContent()[i] == requiredData[i]);
	}

	image.free();
}

TEST_CASE("Image class can read transparent png images", "[Image]") {
	unsigned char requiredData[] = {
		130, 63 , 130, 255,
		126, 87 , 194, 255,
		101, 53 , 54 , 255,
		42 , 54 , 177, 255,
		150, 101, 21 , 139,
		205, 220, 57 , 255,
		33 , 33 , 33 , 0  ,
		18 , 216, 18 , 109,
		156, 204, 101, 255
	};

	Jade::Resources::Image image("assets\\pngTransparentTest.png", false);

	for (int i = 0; i < 36; i++) {
		REQUIRE(image.getContent()[i] == requiredData[i]);
	}

	image.free();
}

TEST_CASE("Image class can read number of channels, width and height from png images", "[Image]") {
	Jade::Resources::Image image("assets\\pngTest.png");
	REQUIRE(image.getChannels() == 4);
	REQUIRE(image.getHeight() == 3);
	REQUIRE(image.getWidth() == 3);

	image.free();
}

TEST_CASE("Image class can read data from jpg images", "[Image]") {
	unsigned char requiredData[] = {
		167, 37 , 37 ,
		253, 220, 189,
		49 , 208, 115,
		193, 64 , 95 ,
		255, 239, 255,
		102, 214, 198,
		79 , 0  , 46 ,
		148, 68 , 179,
		1  , 18 , 160
	};

	Jade::Resources::Image image("assets\\jpgTest.jpg", false);

	for (int i = 0; i < 27; i++) {
		REQUIRE(image.getContent()[i] == requiredData[i]);
	}

	image.free();
}

TEST_CASE("Image class can read number of channels, width and height from jpg images", "[Image]") {
	Jade::Resources::Image image("assets\\jpgTest.jpg", false);
	REQUIRE(image.getChannels() == 3);
	REQUIRE(image.getHeight() == 3);
	REQUIRE(image.getWidth() == 3);

	image.free();
}