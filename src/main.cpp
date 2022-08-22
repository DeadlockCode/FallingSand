#include "engine/BaseApplication.h"
#include "World.h"

World world(256, 256);


int brushRadius = 5;
static void brush(u64 x, u64 y, CellType type) {
	for (int xa = -brushRadius; xa <= brushRadius; xa++) {
		for (int ya = -brushRadius; ya <= brushRadius; ya++) {
			if (world.InBounds(x + xa, y + ya) && std::sqrt(xa * xa + ya * ya) < brushRadius) {
				if (type == CellType::VOID) {
					world.CreateCell(x + xa, y + ya, type);
				}
				else if (world.IsVoid(x + xa, y + ya)) {
					if (type == CellType::FIRE || type == CellType::EMBER) {
						if ((world.m_rng() % 100) < 5)
							world.CreateCell(x + xa, y + ya, type);
					}
					else {
						world.CreateCell(x + xa, y + ya, type);
					}
				}
			}
		}
	}
}

s64 prevx = -1, prevy = -1;
static void updateBrush(CellType type, double mx, double my) {

	CellType inHand;
	if (type != (CellType)-1) {
		inHand = type;
	}
	else {
		prevx = -1; prevy = -1;
		return;
	}


	u64 x, y;
	world.MouseToCell(mx, my, x, y, 800, 800);

	s64 px = prevx, py = prevy;
	if (px == -1 && py == -1) {
		brush(x, y, inHand);
		prevx = x; prevy = y;
		return;
	}

	s64 dx = x - px, dy = y - py;
	u64 dmax = std::max(abs(dx), abs(dy));
	if (dmax == 0) {
		brush(x, y, inHand);
		prevx = x; prevy = y;
		return;
	}

	float rx = (float)dx / dmax, ry = (float)dy / dmax;
	float ix = (float)prevx, iy = (float)prevy;
	for (int i = 0; i < dmax; i++) {
		ix += rx;
		iy += ry;
		brush((u64)round(ix), (u64)round(iy), inHand);
	}
	prevx = x; prevy = y;
}

const char* cellTypes[] = {
	"Delete",
	"Bedrock",
	"Sand",
	"Water",
	"Wood",
	"Fire",
	"Smoke",
	"Ember"
};

bool gui = true;

class Application : public BaseApplication {
	xorshift m_rng = xorshift();

	int selectedCell = 1;
public:
	void Start() {
	}
	void Update() {
		if (!gui) {
			double x, y;
			GetMousePos(x, y);         // casting from selectedCell does not work with new CellType
			if (GetButton(0)) updateBrush((CellType)selectedCell, x, y);
			else              updateBrush((CellType)(-1), x, y);
			world.Update();
		}
	}
	void Draw() {
		for (u64 i = 0; i < world.GetWidth() * world.GetHeight(); i++) {
			u32 color = world.GetColor(i);
			SetPixel(i, color);
		}
	}
	void OnImGui() {
		if (ImGui::IsKeyPressed(512, false))
			gui = !gui;
		if (gui) {
			ImGui::Begin("GUI", (bool*)0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowFontScale(3);
			ImGui::SliderInt("Brush Radius", &brushRadius, 1, 100);
			ImGui::ListBox("Cell Type", &selectedCell, cellTypes, 8);
			ImGui::End();

		}
		//double x, y;
		//u64 cx, cy;
		//GetMousePos(x, y);
		//world.MouseToCell(x, y, cx, cy, 800, 800);
		//if (world.IsLiquid(cx, cy)) {
		//	ImGui::Text("%i, %i", world.GetXVelocity(cx, cy), world.GetYVelocity(cx, cy));
		//}
	}
	void Quit() {

	}
};

int main(void) {
	Application app;
	app.Run();
	return 0;
}
