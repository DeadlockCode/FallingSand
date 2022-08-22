#pragma once

#include "../Element.h"

class Solid : public Element
{
public:
	virtual ~Solid() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override;

	virtual CellType GetType() = 0;

	virtual bool IsSolid() { return true; }
};

