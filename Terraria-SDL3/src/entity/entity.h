#pragma once

namespace Terraria
{
	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}

		virtual void Update(float deltaTime) {}
	};
}