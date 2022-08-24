#include "Fire.h"

#include "../../../../World.h"

void Spread(u64 x, u64 y, World* world) {
	if (world->InBounds(x - 1, y)) { // Left
		CellType type = world->GetType(x - 1, y);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 100) < 10) {
				world->CreateCell(x - 1, y, CellType::FIRE);
			}
		}
		else if (type == CellType::WATER) {
			if ((world->m_rng() % 100) < 50) {
				world->CreateCell(x - 1, y, CellType::STEAM);
				world->CreateCell(x, y, CellType::SMOKE);
			}
		}
	}
	if (world->InBounds(x, y - 1)) { // Down
		CellType type = world->GetType(x, y - 1);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 100) < 10) {
				world->CreateCell(x, y - 1, CellType::FIRE);
			}
		}
		else if (type == CellType::WATER) {
			if ((world->m_rng() % 100) < 50) {
				world->CreateCell(x, y - 1, CellType::STEAM);
				world->CreateCell(x, y, CellType::SMOKE);
			}
		}
	}
	if (world->InBounds(x + 1, y)) { // Right
		CellType type = world->GetType(x + 1, y);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 100) < 10) {
				world->CreateCell(x + 1, y, CellType::FIRE);
			}
		}
		else if (type == CellType::WATER) {
			if ((world->m_rng() % 100) < 50) {
				world->CreateCell(x + 1, y, CellType::STEAM);
				world->CreateCell(x, y, CellType::SMOKE);
			}
		}
	}
	if (world->InBounds(x, y + 1)) { // Up
		CellType type = world->GetType(x, y + 1);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 100) < 10) {
				world->CreateCell(x, y + 1, CellType::FIRE);
			}
		}
		else if (type == CellType::WATER) {
			if ((world->m_rng() % 100) < 50) {
				world->CreateCell(x, y + 1, CellType::STEAM);
				world->CreateCell(x, y, CellType::SMOKE);
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
	Spread(x, y, world);
}
