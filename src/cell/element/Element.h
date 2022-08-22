#pragma once

#include "../Cell.h"

class Element : public Cell
{
protected:
	int m_xVel = 0;
	int m_yVel = 0;
public:
	virtual ~Element() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override = 0;

	virtual CellType GetType() = 0;
};				   