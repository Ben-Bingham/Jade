#pragma once
#include "Core Systems/Logging/Log.h"

namespace Jade {
	class Gameobject;

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

		Gameobject getGameobject();

		void setGameobject(std::shared_ptr<Gameobject> gameobject) { m_Gameobject = gameobject; }

		void update();
		void begin();
		void cleanup();

	private:
		std::shared_ptr<Gameobject> m_Gameobject{};
	};
}