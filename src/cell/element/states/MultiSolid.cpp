#include "MultiSolid.h"

#include "../../../World.h"

void MultiSolid::Step(u64 x, u64 y, World* world)
{
	if (world->IsVoid(x, y - 1) || world->IsLiquid(x, y - 1) || world->IsGas(x, y - 1)) {
		m_yVel--;
	}
	else {
		if (m_yVel < 0) {
			if (m_xVel < 0)
				m_xVel += m_yVel;
			else if (m_xVel > 0)
				m_xVel -= m_yVel;
			else
				m_xVel += ((world->m_rng() & 1) * 2 - 1) * m_yVel;
		}

		m_xVel = (int)((float)m_xVel * (world->m_rng() % 100 < 5 ? 0.5f : 1.0f));

		bool left = false, right = false;

		if (world->IsVoid(x - 1, y - 1) || world->IsLiquid(x - 1, y - 1) || world->IsGas(x - 1, y - 1)) {
			left = true;
		}

		if (world->IsVoid(x + 1, y - 1) || world->IsLiquid(x + 1, y - 1) || world->IsGas(x + 1, y - 1)) {
			right = true;
		}

		if (left && right) {
			left = world->m_rng() & 1;
			right = !left;
		}

		if (left) m_xVel--;
		else if (right) m_xVel++;
	}

	world->Move(x, y, m_xVel, m_yVel);
}
