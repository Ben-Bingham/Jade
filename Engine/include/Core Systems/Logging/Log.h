#pragma once
#include <string>
#include <iostream>

namespace Jade {
	enum LogLevel {
		INFO,
		WARNING,
		ERROR
	};

	class Log {
	public:
		Log(LogLevel logLevel = INFO, bool printFile = true) : m_LogLevel(logLevel), m_PrintFile(printFile) {}

		void log(int lineNumber, const char* file, const std::string& message, LogLevel messageLevel = INFO) {
			if (messageLevel >= m_LogLevel) {
				switch (messageLevel) {
				default:
				case INFO:
					if (m_PrintFile) {
						std::cout << "Jade info at " << file << ' ' << std::to_string(lineNumber) << std::endl;
					}
					std::cout << "[INFO] " << message << std::endl;
					break;
				case WARNING:
					if (m_PrintFile) {
						std::cout << "\x1BJade warning at " << file << std::to_string(lineNumber) << "\033[0m\t\t" << std::endl;
					}
					std::cout << "\x1B[93m" << "[WARNING] " << message << "\033[0m\t\t" << std::endl;
					break;
				case ERROR:
					if (m_PrintFile) {
						std::cout << "\x1BJade error at " << file << std::to_string(lineNumber) << "\033[0m\t\t" << std::endl;
					}
					std::cout << "\x1B[91m" << "[ERROR] " << message << "\033[0m\t\t" << std::endl;
					break;
				}
			}
		}

		void setLogLevel(LogLevel newLevel) { m_LogLevel = newLevel; }
		LogLevel getLogLevel() { return m_LogLevel; }

	private:
		LogLevel m_LogLevel;
		bool m_PrintFile;
	};
}