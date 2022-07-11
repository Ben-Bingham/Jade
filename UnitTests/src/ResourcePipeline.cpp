#include "Core Systems/Logging/Log.h"
#include "UnitTests.h"
#include "Core Systems/Resource Pipeline/TextFile.h"
#include "Core Systems/Resource Pipeline/Image.h"

// Text files -------------------------------------------------------------------------------------
TEST_CASE("TextFile class can read text files", "[TextFile]") {

	Jade::TextFile file("assets\\Test Text Document.txt");

	std::string string = "This is a test document.\n\nIt has multiple lines.\n\nIt is quite short.\0";

	REQUIRE(file.getContent() == string);
}

TEST_CASE("TextFile class can read empty text files", "[TextFile]") {

	Jade::TextFile file("assets\\Test Text Document2.txt");

	std::string string = "\0";

	REQUIRE(file.getContent() == string);
}

TEST_CASE("TextFile class can save path of file", "[TextFile]") {
	std::string path = "assets\\Test Text Document2.txt";
	Jade::TextFile file(path);

	REQUIRE(file.getPath() == path);
}

TEST_CASE("TextFile can be created via string input", "[TextFile]") {
	std::string content = "This is a text file";
	std::string path = "assets\\Unit Test Text File 1.txt";
	Jade::TextFile file(path, content);
	
	REQUIRE(file.getContent() == content);

	Jade::TextFile file2(path);

	REQUIRE(file2.getContent() == file.getContent());
}

TEST_CASE("TextFile can be created via string input with multiple lines", "[TextFile]") {
	std::string content = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.\n \
		Lorem Ipsum has been the industry's standard dummy text ever since the 1500s,\n \
		when an unknown printer took a galley of type and scrambled it to make a type specimen book.\n \
		It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.\n \
		It was popularised in the 1960s with the release of Letraset sheets containing\n \
		Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.\n";

	std::string path = "assets\\Unit Test Text File 2.txt";
	Jade::TextFile file(path, content);

	REQUIRE(file.getContent() == content);

	Jade::TextFile file2(path);

	REQUIRE(file2.getContent() == file.getContent());
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

	Jade::Image image("assets\\pngTest.png", false);

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

	Jade::Image image("assets\\pngTransparentTest.png", false);

	for (int i = 0; i < 36; i++) {
		REQUIRE(image.getContent()[i] == requiredData[i]);
	}

	image.free();
}

TEST_CASE("Image class can read number of channels, width and height from png images", "[Image]") {
	Jade::Image image("assets\\pngTest.png");
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

	Jade::Image image("assets\\jpgTest.jpg", false);

	for (int i = 0; i < 27; i++) {
		REQUIRE(image.getContent()[i] == requiredData[i]);
	}

	image.free();
}

TEST_CASE("Image class can read number of channels, width and height from jpg images", "[Image]") {
	Jade::Image image("assets\\jpgTest.jpg", false);
	REQUIRE(image.getChannels() == 3);
	REQUIRE(image.getHeight() == 3);
	REQUIRE(image.getWidth() == 3);

	image.free();
}