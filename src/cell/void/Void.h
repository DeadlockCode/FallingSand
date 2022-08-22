#pragma once

#include "../Cell.h"

class Void : public Cell
{
public:
	Void() {
		m_color = 0x00000000;
	}

	virtual ~Void() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override {}

	virtual CellType GetType() override { return CellType::VOID; }

	virtual bool IsVoid() override { return true; }
};

