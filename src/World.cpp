#include "World.h"

#include "cell/element/states/_/Sand.h"
#include "cell/void/Void.h"

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

bool World::Down(u64 x, u64 y) {

	bool down = IsVoid(x, y - 1);

	if (down) {
		SwapCells(x, y, x, y - 1);
	}

	return down;
}

bool World::DiagonallyDown(u64 x, u64 y) {
	bool left = IsVoid(x - 1, y - 1);
	bool right = IsVoid(x + 1, y - 1);

	if (left && right) {
		left = m_rng() & 1;
		right = !left;
	}

	if (left) SwapCells(x, y, x - 1, y - 1);
	else if (right) SwapCells(x, y, x + 1, y - 1);

	return left || right;
}

bool World::Side(u64 x, u64 y) {
	bool left = IsVoid(x - 1, y);
	bool right = IsVoid(x + 1, y);

	if (left && right) {
		left = m_rng() & 1;
		right = !left;
	}

	if (left) SwapCells(x, y, x - 1, y);
	else if (right) SwapCells(x, y, x + 1, y);

	return left || right;
}

void World::Move(u64 xFrom, u64 yFrom, int xVel, int yVel) {
	if ((xVel == 0) && (yVel == 0)) return;

	int x1 = xFrom, y1 = yFrom, x2 = xFrom + xVel, y2 = yFrom + yVel;

	int xDiff = x1 - x2;
	int yDiff = y1 - y2;
	bool xDiffIsLarger = std::abs(xDiff) > std::abs(yDiff);

	int xModifier = xDiff < 0 ? 1 : -1;
	int yModifier = yDiff < 0 ? 1 : -1;

	int max = std::max(std::abs(xDiff), std::abs(yDiff));
	int min = std::min(std::abs(xDiff), std::abs(yDiff));
	float slope = (min == 0 || max == 0) ? 0 : ((float)(min + 1) / (max + 1));

	int smallerCount;
	int xTo = xFrom;
	int yTo = yFrom;
	for (int largerCount = 1; largerCount <= max; largerCount++) {
		smallerCount = (int)std::floor(largerCount * slope);
		int yIncrease, xIncrease;
		if (xDiffIsLarger) {
			xIncrease = largerCount;
			yIncrease = smallerCount;
		}
		else {
			yIncrease = largerCount;
			xIncrease = smallerCount;
		}
		int yNext = y1 + (yIncrease * yModifier);
		int xNext = x1 + (xIncrease * xModifier);
		if (IsVoid(xNext, yNext)) {
			xTo = xNext;
			yTo = yNext;
		}
		else {
			break;
		}
	}
	SwapCells(xFrom, yFrom, xTo, yTo);
}