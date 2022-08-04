#include <iostream>
#include <fstream>

#include "Log.h"

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	TextFile::TextFile(const std::string& newPath) : m_Path(newPath), m_Content("") {
		std::ifstream inputFileStream;

		inputFileStream.open(m_Path);
		if (!inputFileStream) {
			LOG("Unable to open text file: " + m_Path, ERROR);
		}

		char character;
		while (inputFileStream >> std::noskipws >> character) {
			m_Content += character;
		}

		inputFileStream.close();
	}

	TextFile::TextFile(const std::string& path, const std::string& content) : m_Path(path), m_Content(content) {
		std::ofstream outFile(m_Path);

		outFile << m_Content;

		outFile.close();
	}
}