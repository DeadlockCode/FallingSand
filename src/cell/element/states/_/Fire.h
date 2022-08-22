#pragma once

#include "../../Element.h"

class Fire : public Element
{
protected:
	u8 m_lifetime;

public:
	Fire() {
		m_lifetime = rand() % 64;
		float t = (rand() % 10000) / 10000.0f;
		m_color = 0xff << 24 | lerp(0x00, 0x08, t) << 16 | lerp(0x00, 0xe8, t) << 8 | lerp(0xff, 0xff, t);
	}

	virtual ~Fire() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override;

	virtual CellType GetType() override { return CellType::FIRE; }
};

