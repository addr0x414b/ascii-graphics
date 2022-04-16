#include <iostream>
#include <unistd.h>
#include <vector>
#include <math.h>
#include <algorithm>

int gScreenWidth = 100;
int gScreenHeight = 40;
char gPrintChar = '#';
std::string gShadeValues = ".:=+*#%@";

typedef struct Vert {
	float x, y, z;
	Vert() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vert(float x1, float y1, float z1) {
		x = x1;
		y = y1;
		z = z1;
	}
} Vert;

typedef struct Trig {
	Vert verts[3];
	Trig(Vert a, Vert b, Vert c) {
		verts[0] = a;
		verts[1] = b;
		verts[2] = c;
	}
} Trig;

class Screen {
	public:
		std::vector<std::vector<char>> buffer;
		int height;
		int width;
		char printChar;

		Screen(unsigned int w, unsigned int h, char pChar) {
			width = w;
			height = h;
			printChar = pChar;
			buffer.resize(height, std::vector<char>(width, printChar));
		}

		void print() {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					std::cout << buffer[y][x];
				}
				std::cout << "\n";
			}
			usleep(10000);
		}

		void clear() {
			buffer.clear();
			buffer.resize(height, std::vector<char>(width, printChar));
		}

		/*
			 void worldToScreen(Vert p, Vert& d) {
			 d.x = round(((p.x * width)+width)/2.f);
//d.y = abs(round(((p.y * height)-height)/2.f));
if (p.y >= 0.0f) {
d.y = (height/2.f) - ((height/2.f) * p.y);
} else {
d.y = ((height/2.f) * abs(p.y)) + (height/2.f);
}
//std::cout << ((height/2.f) * p.y) + (height/2.f) << " ";
//std::cout << d.y << " ";
d.z = p.z;
}*/

void drawPoint(Vert p, char c) {
	//int xn = round(((p.x * width)+width)/2.f);
	//int yn = abs(round(((p.y * height)-height)/2.f));
	//Vert v;
	//worldToScreen(p, v);
	if (p.x < width && p.y < height) {
		buffer[p.y][p.x] = c;
	}
}

void drawTrig(Trig t, char c) {
	std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
			return a.x < b.x;
			});
	//Vert zero;
	//Vert one;
	//Vert two;
	//worldToScreen(t.verts[0], zero);
	//worldToScreen(t.verts[1], one);
	//worldToScreen(t.verts[2], two);
	//Trig n(zero, one, two);
	float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
	float b1 = t.verts[0].y - (m1*t.verts[0].x);
	drawLine(t.verts[0].x, t.verts[1].x, t.verts[0].y, t.verts[1].y, m1, b1, c);
	float m2 = (t.verts[1].y - t.verts[2].y) / (t.verts[1].x - t.verts[2].x);
	float b2 = t.verts[1].y - (m2*t.verts[1].x);
	drawLine(t.verts[1].x, t.verts[2].x, t.verts[1].y, t.verts[2].y, m2, b2, c);
	float m3 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
	float b3 = t.verts[0].y - (m3*t.verts[0].x);
	drawLine(t.verts[0].x, t.verts[2].x, t.verts[0].y, t.verts[2].y, m3, b3, c);
}

void drawLine(int xl, int xr, int yl, int yr, float m, float b, char c) {
	if (xl == xr) {
		if (yl < yr) {
			for (int y = yl; y <= yr; y++) {
				buffer[y][xl] = c;
			}
		} else if (yr < yl) {
			for (int y = yr; y <= yl; y++) {
				buffer[y][xl] = c;
			}
		} else {
			buffer[yr][xl] = c;
		}
	} else {
		for (int x = xl; x <= xr; x++) {
			int y = round((m*x) + b);
			if (y < height) {
				buffer[y][x] = c;
			}
		}
	}
}

/*
	 void fbTrig(Trig t, char c) {
	 if (t.verts[0].y - t.verts[2].y == 0.0f || t.verts[0].y - t.verts[1].y == 0.0f) {
	 std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
	 return a.x < b.x;
	 });
	 drawLine(t.verts[0].x, t.verts[2].x, t.verts[0].y, t.verts[2].y, 0, t.verts[0].y, c);
	 std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
	 return a.y < b.y;
	 });
	 }
	 else if (t.verts[0].x - t.verts[1].x == 0.0f) {
	 float m2 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
	 float b2 = t.verts[0].y - (m2*t.verts[0].x);
	 for (int y = t.verts[0].y; y < t.verts[2].y; y++) {
	 int x1 = t.verts[0].x;
	 int x2 = (y-b2) / m2;
	 if (x1 < x2) {
	 drawLine(x1, x2, y, y, 0, y, c);
	 } else if(x2 < x1) {
	 drawLine(x2, x1, y, y, 0, y, c);
	 } else if (x1 == x2) {
	 drawLine(t.verts[0].x, t.verts[0].x, t.verts[0].y, t.verts[2].y, 0, t.verts[0].y, c);
	 }
	 else {
	 std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
	 return a.x < b.x;
	 });
	 drawLine(t.verts[0].x, t.verts[2].x, t.verts[0].y, t.verts[2].y, 0, t.verts[0].y, c);
	 std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
	 return a.y < b.y;
	 });
	 }
	 }
	 } else if (t.verts[0].x - t.verts[2].x == 0.0f) {
	 float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
	 float b1 = t.verts[0].y - (m1*t.verts[0].x);

	 for (int y = t.verts[0].y; y < t.verts[2].y; y++) {
	 int x1 = (y-b1) / m1;
	 int x2 = t.verts[0].x;
	 if (x1 < x2) {
	 drawLine(x1, x2, y, y, 0, y, c);
	 } else if(x2 < x1) {
	 drawLine(x2, x1, y, y, 0, y, c);
	 }else if (x1 == x2) {
	 drawLine(t.verts[0].x, t.verts[0].x, t.verts[0].y, t.verts[2].y, 0, t.verts[0].y, c);
	 } else {
	 std::cout << "HERE";
	 std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
	 return a.x < b.x;
	 });
	 drawLine(t.verts[0].x, t.verts[2].x, t.verts[0].y, t.verts[2].y, 0, t.verts[0].y, c);
	 std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
	 return a.y < b.y;
	 });
	 }
	 }

	 }
	 else {
	 float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
	 float b1 = t.verts[0].y - (m1*t.verts[0].x);
	 float m2 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
	 float b2 = t.verts[0].y - (m2*t.verts[0].x);

	 for (int y = t.verts[0].y; y < t.verts[2].y; y++) {
	 int x1 = (y-b1) / m1;
	 int x2 = (y-b2) / m2;
	 if (x1 < x2) {
	 drawLine(x1, x2, y, y, 0, y, c);
} else if (x2 > x1) {
	drawLine(x2, x1, y, y, 0, y, c);
} else {
	std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
			return a.x < b.x;
			});
	drawLine(t.verts[0].x, t.verts[2].x, t.verts[0].y, t.verts[2].y, 0, t.verts[0].y, c);
	std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
			return a.y < b.y;
			});
}
}
}
}*/

void drawSLine(int xl, int xr, int y, char c) {
	for (int x = xl; x <= xr; x++) {
		buffer[y][x] = c;
	}
}

void fbTrig(Trig t, char c) {
	if (t.verts[0].x - t.verts[2].x == 0.0f) {
		float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
		float b1 = t.verts[0].y - (m1*t.verts[0].x);
		for (int y = t.verts[0].y; y <= t.verts[2].y; y++) {
			float x1 = t.verts[0].x;
			float x2 = (y - b1) / m1;
			if (x1 == x2) {
				drawLine(x1, x2, y, y, 0, y, c);
			}
			else if (x1 < x2) {
				drawLine(x1, x2, y, y, 0, y, c);
			} else if (x2 < x1) {
				drawLine(x2, x1, y, y, 0, y, c);
			}

		}
	}
	else if (t.verts[0].x - t.verts[1].x == 0.0f) {
		float m2 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
		float b2 = t.verts[0].y - (m2*t.verts[0].x);
		for (int y = t.verts[0].y; y <= t.verts[2].y; y++) {
			float x1 = t.verts[0].x;
			float x2 = (y - b2) / m2;
			if (x1 == x2) {
				drawLine(x1, x2, y, y, 0, y, c);
			}
			else if (x1 < x2) {
				drawLine(x1, x2, y, y, 0, y, c);
			} else if (x2 < x1) {
				drawLine(x2, x1, y, y, 0, y, c);
			}

		}
	} else {
		float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
		float b1 = t.verts[0].y - (m1*t.verts[0].x);
		float m2 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
		float b2 = t.verts[0].y - (m2*t.verts[0].x);

		for (int y = t.verts[0].y; y <= t.verts[2].y; y++) {
			float x1 = (y - b1) / m1;
			float x2 = (y - b2) / m2;
			if (x1 == x2) {
				drawLine(x1, x2, y, y, 0, y, c);
			}
			else if (x1 < x2) {
				drawLine(x1, x2, y, y, 0, y, c);
			} else if (x2 < x1) {
				drawLine(x2, x1, y, y, 0, y, c);
			}

		}
	}

}

void fillTrig(Trig t, char c) {
	std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
			return a.y < b.y;
			});
	if(t.verts[1].y == t.verts[2].y) {
		fbTrig(t, c);
	}
}

};

int main() {

	Screen screen(gScreenWidth, gScreenHeight, ' ');
	Vert p2(50.0f, 1.0f, 0.0f);
	Vert p3(25.0f, 30.0f, 0.0f);
	Vert p1(75.0f, 30.0f, 0.0f);
	Trig t1(p1, p2, p3);

	float slope = 0.1f;
	while (1) {
		std::system("clear");
		screen.drawTrig(t1, 'o');
		screen.fillTrig(t1, '*');
		screen.print();
		screen.clear();
		slope += 0.001f;
	}

	return 0;
}
