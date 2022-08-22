#include "World.h"

World::World(u64 width, u64 height)
	: m_width(width), m_height(height)
{
	m_cells = std::vector<std::unique_ptr<Cell>>();
	m_cells.reserve(m_width * m_height);
	m_order = new u64[m_width * m_height];

	for (u64 i = 0; i < m_width * m_height; i++) {
		m_cells.push_back(std::move(Cell::Create(CellType::VOID)));
		m_order[i] = i;
	}
	for (u64 i = 0; i < m_width * m_height; i++)
	{
		u64 j = i + m_rng() % (m_width * m_height - i);
		std::swap(m_order[i], m_order[j]);
	}
}

World::~World() 
{
	delete[] m_order;
}

void World::Update() 
{
	for (u64 i = 0; i < m_width * m_height; i++)
	{
		u64 j = i + m_rng() % (m_width * m_height - i);
		std::swap(m_order[i], m_order[j]);

		u64 k = m_order[i];

		m_cells[k]->Step(k % m_width, k / m_width, this);
	}
}

void World::Move(u64 xFrom, u64 yFrom, int& xVel, int& yVel) {
	if ((xVel == 0) && (yVel == 0)) return;

	bool xVelIsLarger = std::abs(xVel) > std::abs(yVel);
	bool xVelyVelSame = std::abs(xVel) == std::abs(yVel);

	int xModifier = xVel > 0 ? 1 : -1;
	int yModifier = yVel > 0 ? 1 : -1;

	int max = std::max(std::abs(xVel), std::abs(yVel));
	int min = std::min(std::abs(xVel), std::abs(yVel));
	float slope = (min == 0 || max == 0) ? 0 : ((float)(min + 1) / (max + 1));

	int smallerCount;
	int xTo = xFrom;
	int yTo = yFrom;
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
		u64 xNext = xFrom + ((u64)xIncrease * xModifier);
		u64 yNext = yFrom + ((u64)yIncrease * yModifier);
		if (IsVoid(xNext, yNext) || (IsLiquid(xNext, yNext) && IsSolid(xTo, yTo)) || (IsGas(xNext, yNext) && IsSolid(xTo, yTo)) || (IsGas(xNext, yNext) && IsLiquid(xTo, yTo))) {
			SwapCells(xTo, yTo, xNext, yNext);
			xTo = xNext;
			yTo = yNext;
		}
		else {
			if (xVelyVelSame) {
				xVel = 0;
				yVel = 0;
			}
			else if (xVelIsLarger) {
				xVel = 0;
			}
			else {
				yVel = 0;
			}
			break;
		}
	}
}