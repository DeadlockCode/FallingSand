#pragma once

#include "../Element.h"

class Liquid : public Element
{
protected:
	bool m_goingLeft = false;

	u64 lastx, lasty;
public:
	virtual ~Liquid() override {
	}

	virtual CellType GetType() = 0;

	virtual void Step(u64 x, u64 y, World* world) override;

	virtual bool IsLiquid() { return true; }
};

