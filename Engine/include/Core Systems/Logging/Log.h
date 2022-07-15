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
		Log(LogLevel logLevel = INFO) : m_LogLevel(logLevel) {}

		void log(const std::string& message, LogLevel messageLevel) {
			if (messageLevel >= m_LogLevel) {
				switch (messageLevel) {
				default:
				case INFO:
					std::cout << "[INFO] " << message << std::endl;
					break;
				case WARNING:
					std::cout << "\x1B[93m" << "[WARNING] " << message << "\033[0m\t\t" << std::endl;
					break;
				case ERROR:
					std::cout << "\x1B[91m" << "[ERROR] " << message << "\033[0m\t\t" << std::endl;
					break;
				}
			}
		}

		void setLogLevel(LogLevel newLevel) { m_LogLevel = newLevel; }
		LogLevel getLogLevel() { return m_LogLevel; }

	private:
		LogLevel m_LogLevel;
	};
}
