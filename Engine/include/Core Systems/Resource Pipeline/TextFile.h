#pragma once
#include <iostream>
#include <fstream>

#include "Jade.h"

namespace Jade {
	class TextFile {
	public:
		TextFile() {}
		TextFile(std::string& path) { setPath(path); }
		TextFile(std::string&& path) { setPath(path); }

		TextFile(const std::string& path, const std::string& content);

		std::string getContent() { return m_Content; }
		std::string getPath() { return m_Path; } 
			
		void setPath(std::string& newPath);
		void setPath(std::string&& newPath);

		void append(const std::string& content);

	private:
		std::string m_Path;
		std::string m_Content;
	};
}
