#include "Common.h"

u8 lerp(u8 a, u8 b, float t)
{
	return (u8)(a + t * (b - a));
}
