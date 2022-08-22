#include "Liquid.h"

#include "../../../World.h"

void Liquid::Step(u64 x, u64 y, World* world)
{
	if (world->IsVoid(x, y - 1) || world->IsGas(x, y - 1)) {
		m_yVel--;
	}
	else {
		m_xVel = m_xVel > 5 ? 5 : m_xVel;
		m_xVel = m_xVel < -5 ? -5 : m_xVel;

		bool left = false, right = false;
		
		if (m_xVel <= 0 && world->IsVoid(x - 1, y) || world->IsGas(x - 1, y)) {
			left = true;
		}

		if (m_xVel >= 0 && world->IsVoid(x + 1, y) || world->IsGas(x + 1, y)) {
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
