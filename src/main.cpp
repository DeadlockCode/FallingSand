#include "engine/BaseApplication.h"
#include "World.h"

World world(256, 256);

void horizontal_line(u64 x0, u64 x1, u64 y, CellType type) {
	for (u64 x = x0; x < x1; x++) {
		if (world.InBounds(x, y)) {
			if (type == CellType::VOID) {
				world.CreateCell(x, y, type);
			}
			else if (world.IsVoid(x, y)) {
				if (type == CellType::FIRE || type == CellType::EMBER) {
					if ((world.m_rng() % 100) < 5)
						world.CreateCell(x, y, type);
				}
				else {
					world.CreateCell(x, y, type);
				}
			}
		}
	}
}

void circle_helper(u64 x, u64 y, u64 i, u64 j, CellType type) {
	horizontal_line(x - i, x + i, y + j, type);
	horizontal_line(x - i, x + i, y - j, type);
	horizontal_line(x - j, x + j, y + i, type);
	horizontal_line(x - j, x + j, y - i, type);
}

int brushRadius = 5;
static void brush(u64 x, u64 y, CellType type) {
	float i = 0.0;
	float j = brushRadius;
	float d = 3.0 - 2.0 * brushRadius;

	circle_helper(x, y, i, j, type);

	while (i <= j) {
		if (d <= 0.0) {
			d += (4.0 * i) + 6.0;
		}
		else
		{
			d += (4.0 * i) - (4.0 * j) + 10.0;
			j -= 1.0;
		}
		i += 1.0;

		circle_helper(x, y, i, j, type);
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
