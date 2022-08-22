#include "Gas.h"

#include "../../../World.h"

void Gas::Step(u64 x, u64 y, World* world)
{
	//if (y + 1 < world->GetHeight()) {
	//	Cell* up = world->GetCell(x, y + 1);
	//	if (up->GetType() == GetType()) {
	//		float total = m_density + up->GetDensity();
	//		m_density = total / 2;
	//		up->SetDensity(total / 2);
	//	}
	//}
	//if (y > 0) {
	//	Cell* down = world->GetCell(x, y - 1);
	//	if (down->GetType() == GetType()) {
	//		float total = m_density + down->GetDensity();
	//		m_density = total / 2;
	//		down->SetDensity(total / 2);
	//	}
	//}
	//if (x + 1 < world->GetWidth()) {
	//	Cell* right = world->GetCell(x + 1, y);
	//	if (right->GetType() == GetType()) {
	//		float total = m_density + right->GetDensity();
	//		m_density = total / 2;
	//		right->SetDensity(total / 2);
	//	}
	//}
	//if (x > 0) {
	//	Cell* left = world->GetCell(x - 1, y);
	//	if (left->GetType() == GetType()) {
	//		float total = m_density + left->GetDensity();
	//		m_density = total / 2;
	//		left->SetDensity(total / 2);
	//	}
	//}
	//
	//
	//if (y + 1 < world->GetHeight()) {
	//	Cell* up = world->GetCell(x, y + 1);
	//	if (up->IsVoid()) {
	//		float total = m_density;
	//		Cell* cell = Cell::Create(GetType());
	//		cell->SetDensity(total / 2);
	//		world->SetCell(x, y + 1, cell);
	//		m_density = total / 2;
	//	}
	//}
	//if (y > 0) {
	//	Cell* up = world->GetCell(x, y - 1);
	//	if (up->IsVoid()) {
	//		float total = m_density;
	//		Cell* cell = Cell::Create(GetType());
	//		cell->SetDensity(total / 2);
	//		world->SetCell(x, y - 1, cell);
	//		m_density = total / 2;
	//	}
	//}
	//if (x + 1 < world->GetWidth()) {
	//	Cell* up = world->GetCell(x + 1, y);
	//	if (up->IsVoid()) {
	//		float total = m_density;
	//		Cell* cell = Cell::Create(GetType());
	//		cell->SetDensity(total / 2);
	//		world->SetCell(x + 1, y, cell);
	//		m_density = total / 2;
	//	}
	//}
	//if (x > 0) {
	//	Cell* up = world->GetCell(x - 1, y);
	//	if (up->IsVoid()) {
	//		float total = m_density;
	//		Cell* cell = Cell::Create(GetType());
	//		cell->SetDensity(total / 2);
	//		world->SetCell(x - 1, y, cell);
	//		m_density = total / 2;
	//	}
	//}
}
