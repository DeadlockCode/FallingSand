#pragma once

#include "../Gas.h"

class Smoke : public Gas
{
public:

	Smoke() {
		m_color = 0x99383b3b;
	}

	virtual ~Smoke() override {

	}

	virtual CellType GetType() override { return CellType::SMOKE; }
};

