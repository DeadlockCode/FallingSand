#pragma once

#include "../Solid.h"

class Sand : public Solid
{
public:

	Sand() {
		float t = (rand() % 10000) / 10000.0f;
		m_color = 0xff << 24 | lerp(0xb0, 0x93, t) << 16 | lerp(0xd7, 0xba, t) << 8 | lerp(0xf6, 0xe6, t);
	}

	virtual ~Sand() override {
		
	}

	virtual CellType GetType() override { return CellType::SAND; }
};

