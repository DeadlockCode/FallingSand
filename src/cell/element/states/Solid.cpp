#include "Solid.h"

#include "../../../World.h"

void Solid::Step(u64 x, u64 y, World* world)
{
	if (world->IsVoid(x, y - 1)) {
		m_yVel--;
	}
	else {
		if (m_yVel < -3) {
			m_xVel += (world->m_rng() & 1) * 2 - 1;
		}

		m_xVel = (int)((float)m_xVel * (world->m_rng() % 100 < 5 ? 0.5f : 1.0f));

		bool left = false, right = false;

		if (m_xVel < 0 && !world->IsVoid(x - 1, y)) {
			m_xVel = 0;
		}
		else {
			if (world->IsVoid(x - 1, y - 1)) {
				left = true;
			}
		}

		if (m_xVel > 0 && !world->IsVoid(x + 1, y)) {
			m_xVel = 0;
		}
		else {
			if (world->IsVoid(x + 1, y - 1)) {
				right = true;
			}
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
