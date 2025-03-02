#include "conversion.h"
#include "world/world.h"

namespace Terraria
{
	void ScreenToTileCoordinates(float& x, float& y, const World& world)
	{
		x /= static_cast<float>(world.tileWidth);
		y /= static_cast<float>(world.tileHeight);
	}

}