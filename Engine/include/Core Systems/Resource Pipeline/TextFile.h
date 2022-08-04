#pragma once
#include <iostream>
#include <fstream>

#include "Log.h"

namespace Jade {
	class TextFile {
	public:
		TextFile(const std::string& path);
		TextFile(const std::string& path, const std::string& content);

		std::string getContent() { return m_Content; }
		std::string getPath() { return m_Path; } 
	private:
		std::string m_Path;
		std::string m_Content;
	};
}
