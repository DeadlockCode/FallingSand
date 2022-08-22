#pragma once

#include "../Element.h"

class MonoSolid : public Element
{
public:
	virtual ~MonoSolid() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override {};

	virtual CellType GetType() = 0;

	virtual bool IsSolid() { return true; }
};

