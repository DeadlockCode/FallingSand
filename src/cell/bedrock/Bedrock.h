#pragma once

#include "../Cell.h"

class Bedrock : public Cell
{
public:
	Bedrock() {
		float t = (rand() % 10000) / 10000.0f;
		m_color = 0xff << 24 | lerp(0x22, 0xaa, t * t) << 16 | lerp(0x22, 0xaa, t * t) << 8 | lerp(0x22, 0xaa, t * t);
	}

	virtual ~Bedrock() override {

	}

	virtual void Step(u64 x, u64 y, World* world) override {}

	virtual CellType GetType() override {
		return CellType::BEDROCK;
	}
};