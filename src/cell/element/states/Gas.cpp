#include "Gas.h"

#include "../../../World.h"

void Gas::Step(u64 x, u64 y, World* world)
{
	if ((world->IsVoid(x, y + 1) || world->IsGas(x, y + 1)) && world->m_rng() % 100 < 33) {
		world->SwapCells(x, y, x, y + 1);
	}

	if ((world->IsVoid(x - 1, y) || world->IsGas(x - 1, y)) && world->m_rng() % 100 < 10) {
		world->SwapCells(x, y, x - 1, y);
	}

	if ((world->IsVoid(x + 1, y) || world->IsGas(x + 1, y)) && world->m_rng() % 100 < 10) {
		world->SwapCells(x, y, x + 1, y);
	}
}
