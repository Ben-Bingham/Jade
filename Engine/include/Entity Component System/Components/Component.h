#pragma once
#include "Jade.h"

namespace Jade {
	class Component {
	public:
		Component() {}
		Component(const Component&) = default;
		Component(Component&&) = default;
		Component& operator=(const Component&) = default;
		Component& operator=(Component&&) = default;
		virtual ~Component() = 0;

		virtual void Update() {}
		virtual void Begin() {}
		virtual void Cleanup() {}

		void update();
		void begin();
		void cleanup();
	};
}