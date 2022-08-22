#pragma once

#include "../MonoSolid.h"

class Wood : public MonoSolid
{
public:

	Wood() {
		float t = (rand() % 10000) / 10000.0f;
		m_color = 0xff << 24 | lerp(0x2a, 0x4a, t) << 16 | lerp(0x47, 0x7e, t) << 8 | lerp(0x69, 0xa7, t);
	}

	virtual ~Wood() override {

	}

	virtual CellType GetType() override { return CellType::WOOD; }
};
