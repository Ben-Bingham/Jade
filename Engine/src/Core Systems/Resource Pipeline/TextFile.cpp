#include <iostream>
#include <fstream>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/TextFile.h"

namespace Jade {
	namespace Resources {
		void TextFile::setPath(std::string& newPath) {
			m_Path = newPath;

			std::ifstream inputFileStream;

			inputFileStream.open(m_Path);
			if (!inputFileStream) {
				LOGGER.log("Unable to open text file: " + m_Path, ERROR);
			}

			char character;
			while (inputFileStream >> std::noskipws >> character) {
				m_Content += character;
			}

			inputFileStream.close();
		}

		void TextFile::setPath(std::string&& newPath) {
			m_Path = newPath;

			std::ifstream inputFileStream;

			inputFileStream.open(m_Path);
			if (!inputFileStream) {
				LOGGER.log("Unable to open text file: " + m_Path, ERROR);
			}

			char character;
			while (inputFileStream >> std::noskipws >> character) {
				m_Content += character;
			}

			inputFileStream.close();
		}
	}
}