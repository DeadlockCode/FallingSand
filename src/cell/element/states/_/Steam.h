#pragma once

#include "../Gas.h"

class Steam : public Gas
{
public:

	Steam() {
		m_color = 0x99e0d5c7;
	}

	virtual ~Steam() override {

	}

	virtual CellType GetType() override { return CellType::STEAM; }
};

