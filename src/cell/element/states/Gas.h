#pragma once

#include "../Element.h"

class Gas : public Element
{
public:
	virtual ~Gas() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override;

	virtual CellType GetType() = 0;

	virtual bool IsGas() { return true; }
};

