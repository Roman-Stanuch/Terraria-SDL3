#pragma once

namespace Terraria
{
	class World;

	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}

		virtual void Update(float deltaTime, World& world) {}
	};
}