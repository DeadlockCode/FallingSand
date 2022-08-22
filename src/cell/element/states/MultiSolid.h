#pragma once

#include "../Element.h"

class MultiSolid : public Element
{
public:
	virtual ~MultiSolid() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override;

	virtual CellType GetType() = 0;

	virtual bool IsSolid() { return true; }
};

