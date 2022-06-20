#pragma once
#include <string>
#include <iostream>

namespace Jade {
	template<class Type>
	void print(Type value) {
		std::cout << value << std::endl;
	}

	enum LogLevel {
		INFO,
		WARNING,
		ERROR
	};

	class Log {
	public:
		Log(LogLevel logLevel = INFO) : m_LogLevel(logLevel) {}

		void log(std::string message, LogLevel messageLevel) {
			if (messageLevel >= m_LogLevel) {
				std::cout << message << std::endl;
			}
		}

		void setLogLevel(LogLevel newLevel) { m_LogLevel = newLevel; }
		LogLevel getLogLevel() { return m_LogLevel; }

	private:
		LogLevel m_LogLevel;
	};
}
