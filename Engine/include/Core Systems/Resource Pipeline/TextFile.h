#pragma once
#include <iostream>
#include <fstream>

#include "Jade.h"

namespace Jade {
	namespace Resources {
		class TextFile {
		public:
			TextFile() {}
			TextFile(std::string& path) { setPath(path); }
			TextFile(std::string&& path) { setPath(path); }

			std::string getContent() { return m_Content; }
			std::string getPath() { return m_Path; } 
			
			void setPath(std::string& newPath);
			void setPath(std::string&& newPath);

		private:
			std::string m_Path;
			std::string m_Content;
		};
	}
}
