#include "conversion.h"
#include "world/world.h"

namespace Terraria
{
	void ScreenToTileCoordinates(float& x, float& y, float tileWidth, float tileHeight)
	{
		x /= tileWidth;
		y /= tileHeight;
	}

}