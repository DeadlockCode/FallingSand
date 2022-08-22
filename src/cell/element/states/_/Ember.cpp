#include "Ember.h"

#include "../../../../World.h"

void Ember::Step(u64 x, u64 y, World* world)
{
	// Life & Color
	m_lifetime++;

	if (m_lifetime == 255) {
		world->CreateCell(x, y, CellType::SMOKE);
	}

	float t = (rand() % 10000) / 10000.0f;
	m_color = (0xff - m_lifetime) << 24 | lerp(0x00, 0x08, t) << 16 | lerp(0x00, 0xe8, t) << 8 | lerp(0xff, 0xff, t);

	// Movement
	if (world->IsVoid(x, y + 1) && world->m_rng() % 100 < 33) {
		world->SwapCells(x, y, x, y + 1);
	}

	if (world->IsVoid(x - 1, y) && world->m_rng() % 100 < 10) {
		world->SwapCells(x, y, x - 1, y);
	}

	if (world->IsVoid(x + 1, y) && world->m_rng() % 100 < 10) {
		world->SwapCells(x, y, x + 1, y);
	}

	// Spread
	if (world->InBounds(x - 1, y)) { // Left
		CellType type = world->GetType(x - 1, y);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 1000) < 1) {
				world->CreateCell(x - 1, y, CellType::FIRE);
			}
		}
	}
	if (world->InBounds(x, y - 1)) { // Down
		CellType type = world->GetType(x, y - 1);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 1000) < 1) {
				world->CreateCell(x, y - 1, CellType::FIRE);
			}
		}
	}
	if (world->InBounds(x + 1, y)) { // Right
		CellType type = world->GetType(x + 1, y);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 1000) < 1) {
				world->CreateCell(x + 1, y, CellType::FIRE);
			}
		}
	}
	if (world->InBounds(x, y + 1)) { // Up
		CellType type = world->GetType(x, y + 1);

		if (type == CellType::WOOD) {
			if ((world->m_rng() % 1000) < 1) {
				world->CreateCell(x, y + 1, CellType::FIRE);
			}
		}
	}
}