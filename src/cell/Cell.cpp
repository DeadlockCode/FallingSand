#include "Cell.h"

#include "void/Void.h"
#include "bedrock/Bedrock.h"
#include "element/states/_/Sand.h"
#include "element/states/_/Water.h"
#include "element/states/_/Wood.h"
#include "element/states/_/Fire.h"
#include "element/states/_/Smoke.h"
#include "element/states/_/Ember.h"
#include "element/states/_/Steam.h"

std::unique_ptr<Cell> Cell::Create(CellType type)
{
	switch (type) {
	case CellType::VOID:
		return std::make_unique<Void>();
	case CellType::BEDROCK:
		return std::make_unique<Bedrock>();
	case CellType::SAND:
		return std::make_unique<Sand>();
	case CellType::WATER:
		return std::make_unique<Water>();
	case CellType::WOOD:
		return std::make_unique<Wood>();
	case CellType::FIRE:
		return std::make_unique<Fire>();
	case CellType::SMOKE:
		return std::make_unique<Smoke>();
	case CellType::EMBER:
		return std::make_unique<Ember>();
	case CellType::STEAM:
		return std::make_unique<Steam>();
	default:
		ASSERT(false);
	}
}
