#pragma once

#include "../engine/Common.h"
#include <random>

#include <memory>

class World;

enum class CellType : u8 {
	VOID,
	BEDROCK,
	SAND,
	WATER,
};

class Cell {
protected:
	u32 m_color; 
	bool m_sleeping;
public:
	virtual ~Cell() {

	}

	virtual void Step(u64 x, u64 y, World* world) = 0;

	virtual CellType GetType() = 0;

	virtual u32 GetColor() {
		return m_color;
	}

	static std::unique_ptr<Cell> Create(CellType type);

	virtual bool IsVoid() { return false; }
	virtual bool IsGas() { return false; }
	virtual bool IsLiquid() { return false; }
	virtual bool IsSolid() { return false; }

	bool IsSleeping() { return m_sleeping; }

	virtual u8 GetDensity() { return 0; }
	virtual void SetDensity(u8 value) {}

	virtual int GetXVelocity() { return 0; }
	virtual int GetYVelocity() { return 0; }
};									   