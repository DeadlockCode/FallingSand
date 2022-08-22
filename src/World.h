#pragma once

#include <vector>
#include <random>

#include "engine/Common.h"

#include "xorshift.h"
#include <iostream>
#include <memory>

#include "cell/Cell.h"

class World {
private:
	const u64 m_width;
	const u64 m_height;

	std::vector<std::unique_ptr<Cell>> m_cells;
	u64* m_order = nullptr;

public:
	xorshift m_rng = xorshift();

	World(u64 width, u64 height);

	~World();

	inline u64 GetWidth()              const { return m_width; }
	inline u64 GetHeight()             const { return m_height; }

	inline u64  GetIndex(u64 x, const u64& y) const { return x + y * m_width; }

	void CreateCell(u64 index, CellType type) {
		m_cells[index] = Cell::Create(type); // might need to use std::move
	}
	void CreateCell(u64 x, u64 y, CellType type) {
		m_cells[GetIndex(x, y)] = Cell::Create(type);
	}

	bool InBounds(u64 x, u64 y) { return x < m_width && y < m_height; }

	void MouseToCell(double mX, double mY, u64& cellX, u64& cellY, u64 winWidth, u64 winHeight) {
		cellX = u64(mX * m_width / winWidth);
		cellY = m_height - u64(mY * m_height / winHeight) - 1;
	}

	void SwapCells(u64 x1, u64 y1, u64 x2, u64 y2) {
		std::swap(m_cells[GetIndex(x1, y1)], m_cells[GetIndex(x2, y2)]);
	}

	void Update();

	void Move(u64 xFrom, u64 yFrom, int& xVel, int& yVel);

	bool IsVoid(u64 x, u64 y) {
		return InBounds(x, y) && m_cells[GetIndex(x, y)]->IsVoid();
	}

	bool IsGas(u64 x, u64 y) {
		return InBounds(x, y) && m_cells[GetIndex(x, y)]->IsGas();
	}

	bool IsLiquid(u64 x, u64 y) {
		return InBounds(x, y) && m_cells[GetIndex(x, y)]->IsLiquid();
	}

	bool IsSolid(u64 x, u64 y) {
		return InBounds(x, y) && m_cells[GetIndex(x, y)]->IsSolid();
	}

	bool IsSleeping(u64 x, u64 y) {
		return InBounds(x, y) && m_cells[GetIndex(x, y)]->IsSleeping();
	}

	u32 GetColor(u64 index) {
		return m_cells[index]->GetColor();
	}

	CellType GetType(u64 x, u64 y) {
		return m_cells[GetIndex(x, y)]->GetType();
	}
};

