#include "conversion.h"
#include "world/world.h"

namespace Terraria
{
	void Terraria::ScreenToTileCoordinates(float& x, float& y, World& world)
	{
		x /= world.GetWorldTileWidth();
		y /= world.GetWorldTileHeight();
	}

}