#pragma once

/*
Default header file for the engine, contains many useful includes
*/

#include <string>

#include "Core Systems/Logging/Log.h"

extern Jade::Log LOGGER;

#ifdef JADE_DEBUG
	#define LOG(...) LOGGER.log(__VA_ARGS__)
#else
	#define LOG(...)
#endif // JADE_DEBUG