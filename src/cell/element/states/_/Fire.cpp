#include "Fire.h"

#include "../../../../World.h"

void Spread(u64 x, u64 y, World* world) {
	if (world->InBounds(x, y)) { // Left
		CellType type = world->GetType(x, y);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 100) < 10) {
				world->CreateCell(x, y, CellType::FIRE);
			}
		}
		else if (type == CellType::WATER) {
			if ((world->m_rng() % 100) < 50) {
				world->CreateCell(x, y, CellType::STEAM);
			}
		}
	}
}

void Fire::Step(u64 x, u64 y, World* world)
{
	// Life & Color
	m_lifetime++;

	if (m_lifetime == 64) {
		if (world->m_rng() % 100 < 10) {
			world->CreateCell(x, y, CellType::EMBER);
		}
		else {
			world->CreateCell(x, y, CellType::SMOKE);
		}
		return;
	}

	float t = (world->m_rng() % 10000) / 10000.0f;
	m_color = 0xff << 24 | lerp(0x00, 0x08, t) << 16 | lerp(0x00, 0xe8, t) << 8 | lerp(0xff, 0xff, t);


	// Spread
	Spread(x - 1, y, world);
	Spread(x, y - 1, world);
	Spread(x + 1, y, world);
	Spread(x, y + 1, world);
}
