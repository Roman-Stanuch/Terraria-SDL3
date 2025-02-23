#include "conversion.h"
#include "world/world.h"

namespace Terraria
{
	void Terraria::ScreenToTileCoordinates(float& x, float& y, const World& world)
	{
		x /= world.tileWidth;
		y /= world.tileHeight;
	}

}