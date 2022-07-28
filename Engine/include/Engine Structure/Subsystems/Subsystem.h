#pragma once

namespace Jade {
	class Subsystem {
	public:
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;
	};
}