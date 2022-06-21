#pragma once
#include <iostream>
#include <fstream>

#include "Jade.h"

namespace Jade {
	namespace Resources {
		class TextFile {
		public:
			TextFile(std::string path) : m_Path(path) {
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

			std::string getContent() { return m_Content; }
			std::string getPath() { return m_Path; }

		private:
			std::string m_Path;
			std::string m_Content;
		};
	}
}
