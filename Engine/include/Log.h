#pragma once

#include <string>

#include "Core Systems/Logging/Log.h"

extern Jade::Log LOGGER;

#ifdef JADE_DEBUG
	#define LOG(...) LOGGER.log(__LINE__, __FILE__, __VA_ARGS__)
#else
	#define LOG(...)
#endif // JADE_DEBUG