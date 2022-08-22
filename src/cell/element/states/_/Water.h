#pragma once

#include "../Liquid.h"

class Water : public Liquid
{
protected:
public:
	Water() {
		m_color = 0xffda8923;
	}

	virtual ~Water() override {

	}

	virtual CellType GetType() override { return CellType::WATER; }
};