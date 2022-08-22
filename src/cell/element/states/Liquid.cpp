#include "Liquid.h"

#include "../../../World.h"

void Move(u64 x, u64 y, int& xVel, int& yVel, World* world);

void Move(u64 x, u64 y, int& xVel, int& yVel, World* world) {

	if ((xVel == 0) && (yVel == 0)) return;

	bool xVelIsLarger = std::abs(xVel) > std::abs(yVel);

	int xModifier = xVel > 0 ? 1 : -1;
	int yModifier = yVel > 0 ? 1 : -1;

	int max = std::max(std::abs(xVel), std::abs(yVel));
	int min = std::min(std::abs(xVel), std::abs(yVel));
	float slope = (min == 0 || max == 0) ? 0 : ((float)(min + 1) / (max + 1));

	int smallerCount;
	int xTo = x;
	int yTo = y;
	for (int largerCount = 1; largerCount <= max; largerCount++) {
		smallerCount = (int)std::floor(largerCount * slope);
		int yIncrease, xIncrease;
		if (xVelIsLarger) {
			xIncrease = largerCount;
			yIncrease = smallerCount;
		}
		else {
			yIncrease = largerCount;
			xIncrease = smallerCount;
		}
		int xNext = (int)x + (xIncrease * xModifier);
		int yNext = (int)y + (yIncrease * yModifier);
		if (world->IsVoid(xNext, yNext)) {
			xTo = xNext;
			yTo = yNext;
		}
		else {
			if (xVelIsLarger) {
				xVel = 0;
			}
			else {
				yVel = 0;
			}
			break;
		}
	}


	world->SwapCells(x, y, xTo, yTo);
}

void Liquid::Step(u64 x, u64 y, World* world)
{
	if (world->IsVoid(x, y - 1)) {
		m_yVel--;
	}
	else {
		bool left = false, right = false;
		
		if (world->IsVoid(x - 1, y) && world->IsVoid(x - 1, y - 1)) {
			left = true;
		}

		if (world->IsVoid(x + 1, y) && world->IsVoid(x + 1, y - 1)) {
			right = true;
		}
		
		if (left && right) {
			left = world->m_rng() & 1;
			right = !left;
		}
		
		if (left) m_xVel--;
		else if (right) m_xVel++;
	}

	Move(x, y, m_xVel, m_yVel, world);

	// Saved for if I want to go back to simulating pressure through semi compressible fluids

	//// Go Down ------------------------------------------------------------------------------------------------
	//if (world->InBounds(x, y - 1)) {
	//	CellType type = world->GetType(x, y - 1);
	//
	//	if (type == CellType::VOID) {
	//		world->SwapCells(x, y, x, y - 1);
	//		return; // possible to do "y++;" and continue with other calculations;
	//	}
	//
	//	if (type == GetType()) {
	//		float flow = 0.0f;
	//		float total = m_density + world->GetDensity(x, y - 1);
	//
	//		if (total <= 1.0f)
	//			flow = 1.0f;
	//		else if (total < 2 * m_maxDensity + m_compression)
	//			flow = (m_maxDensity * m_maxDensity + total * m_compression) / (m_maxDensity + m_compression);
	//		else
	//			flow = (total + m_compression) / 2;
	//
	//		flow -= world->GetDensity(x, y - 1);
	//
	//		//flow *= 0.5f;
	//		flow = std::max(0.0f, std::min(flow, m_density));
	//
	//		m_density -= flow;
	//		world->SetDensity(x, y - 1, world->GetDensity(x, y - 1) + flow);
	//	}
	//}
	//
	//if (m_density <= 0.0f) {
	//	world->CreateCell(x, y, CellType::VOID);
	//	return;
	//}
	//
	//// Go Left and Right --------------------------------------------------------------------------------------
	//
	//bool left = false;
	//if (world->InBounds(x - 1, y)) {
	//	CellType type = world->GetType(x - 1, y);
	//
	//	if (type == CellType::VOID) {
	//		world->CreateCell(x - 1, y, GetType());
	//		world->SetDensity(x - 1, y, 0);
	//		left = true;
	//	}
	//
	//	if (type == GetType()) {
	//		left = true;
	//	}
	//}
	//
	//bool right = false;
	//if (world->InBounds(x + 1, y)) {
	//	CellType type = world->GetType(x + 1, y);
	//
	//	if (type == CellType::VOID) {
	//		world->CreateCell(x + 1, y, GetType());
	//		world->SetDensity(x + 1, y, 0);
	//		right = true;
	//	}
	//
	//	if (type == GetType()) {
	//		right = true;
	//	}
	//}
	//
	//if (left && right) {
	//	float flowLeft = (m_density - world->GetDensity(x - 1, y)) * 0.333f;
	//	float flowRight = (m_density - world->GetDensity(x + 1, y)) * 0.333f;
	//
	//	float totalFlow = flowLeft + flowRight;
	//	totalFlow = std::max(0.0f, std::min(totalFlow, m_density));
	//
	//	if (totalFlow != flowLeft + flowRight) {
	//		float change = totalFlow / (flowLeft + flowRight);
	//		flowLeft = flowLeft * change;                        // Might have a mathematical error
	//		flowRight = flowRight * change;
	//	}
	//
	//	m_density -= flowLeft;
	//	world->SetDensity(x - 1, y, world->GetDensity(x - 1, y) + flowLeft);
	//
	//	m_density -= flowRight;
	//	world->SetDensity(x + 1, y, world->GetDensity(x + 1, y) + flowRight);
	//}
	//else if (left) {
	//	float flow = (m_density - world->GetDensity(x - 1, y)) * 0.5f;
	//
	//	flow = std::max(0.0f, std::min(flow, m_density));
	//
	//	m_density -= flow;
	//	world->SetDensity(x - 1, y, world->GetDensity(x - 1, y) + flow);
	//}
	//else if (right) {
	//	float flow = (m_density - world->GetDensity(x + 1, y)) * 0.5f;
	//
	//	flow = std::max(0.0f, std::min(flow, m_density));
	//
	//	m_density -= flow;
	//	world->SetDensity(x + 1, y, world->GetDensity(x + 1, y) + flow);
	//}
	//
	//if (m_density <= 0.0f) {
	//	world->CreateCell(x, y, CellType::VOID);
	//	return;
	//}
	//
	//// Go Up --------------------------------------------------------------------------------------------------
	//if (world->InBounds(x, y + 1)) {
	//	CellType type = world->GetType(x, y + 1);
	//
	//	if (type == CellType::VOID) {
	//		world->CreateCell(x, y + 1, GetType());
	//		world->SetDensity(x, y + 1, 0);
	//	}
	//
	//	if (type == GetType() || type == CellType::VOID) {
	//		float flow = 0.0f;
	//		float total = m_density + world->GetDensity(x, y + 1);
	//
	//		if (total <= 1.0f)
	//			flow = 1.0f;
	//		else if (total < 2 * m_maxDensity + m_compression)
	//			flow = (m_maxDensity * m_maxDensity + total * m_compression) / (m_maxDensity + m_compression);
	//		else
	//			flow = (total + m_compression) / 2;
	//
	//		flow = m_density - flow;
	//
	//		flow *= 0.5f;
	//		flow = std::max(0.0f, std::min(flow, m_density));
	//
	//		m_density -= flow;
	//		world->SetDensity(x, y + 1, world->GetDensity(x, y + 1) + flow);
	//	}
	//}
	//
	//if (m_density <= 0.0f) {
	//	world->CreateCell(x, y, CellType::VOID);
	//	return;
	//}
}
