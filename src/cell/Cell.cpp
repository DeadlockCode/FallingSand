#include "Cell.h"

#include "void/Void.h"
#include "bedrock/Bedrock.h"
#include "element/states/_/Sand.h"
#include "element/states/_/Water.h"

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
	default:
		ASSERT(false);
	}
}
