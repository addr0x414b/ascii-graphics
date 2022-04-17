#include <iostream>
#include <unistd.h>
#include <vector>
#include <math.h>
#include <algorithm>

int gScreenWidth = 100;
int gScreenHeight = 40;
char gPrintChar = '#';
std::string gShadeValues = ".:*+=%#@";
//std::string gShadeValues = ".'`^,:;Il!i><~+_-?][}{1)(|tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

typedef struct Vert {
	float x, y, z, c;
	Vert() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		c = 0.1f;
	}
	Vert(float x1, float y1, float z1, float c1) {
		x = x1;
		y = y1;
		z = z1;
		c = c1;
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

		void drawPoint(Vert p, char c) {
			if (p.x < width && p.y < height) {
				buffer[p.y][p.x] = c;
			}
		}

		void drawTrig(Trig t, char c) {
			std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
					return a.x < b.x;
					});
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
					for (int y = yr; y < yl; y++) {
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

		void shadeLine(int xl, int xr, int yl, int yr, float m, float b, Trig t, Trig orig) {
			if (xl == xr) {
				if (yl < yr) {
					for (int y = yl; y <= yr; y++) {
						//buffer[y][xl] = c;
					}
				} else if (yr < yl) {
					for (int y = yr; y <= yl; y++) {
						//buffer[y][xl] = c;
					}
				} else {
					//buffer[yr][xl] = c;
				}
			} else {
				for (int x = xl; x <= xr; x++) {
					int y = round((m*x) + b);
					if (y < height) {
						float w1 = (((orig.verts[1].y - orig.verts[2].y) * (x - orig.verts[2].x)) + ((orig.verts[2].x - orig.verts[1].x) * (y - orig.verts[2].y))) /
							(((orig.verts[1].y - orig.verts[2].y) * (orig.verts[0].x - orig.verts[2].x)) + ((orig.verts[2].x - orig.verts[1].x) * (orig.verts[0].y - orig.verts[2].y)));
						float w2 = (((orig.verts[2].y - orig.verts[0].y) * (x - orig.verts[2].x)) + ((orig.verts[0].x - orig.verts[2].x) * (y - orig.verts[2].y))) /
							(((orig.verts[1].y - orig.verts[2].y) * (orig.verts[0].x - orig.verts[2].x)) + ((orig.verts[2].x - orig.verts[1].x) * (orig.verts[0].y - orig.verts[2].y)));
						float w3 = 1 - w1 - w2;
						float color = ((w1 * orig.verts[0].c) + (w2 * orig.verts[1].c) + (w3 * orig.verts[2].c)) / (w1 + w2 + w3);
						color = round(8 * color);
						buffer[y][x] = gShadeValues[color-1];
						//buffer[y][x] = '*';
					}
				}
			}
		}

		void drawSLine(int xl, int xr, int y, char c) {
			for (int x = xl; x <= xr; x++) {
				buffer[y][x] = c;
			}
		}

		void fbTrig(Trig t, char c, Trig orig) {
			if (t.verts[0].x - t.verts[2].x == 0.0f) {
				float m1 = (t.verts[0].y - t.verts[1].y) / (t.verts[0].x - t.verts[1].x);
				float b1 = t.verts[0].y - (m1*t.verts[0].x);
				for (int y = t.verts[0].y; y <= t.verts[2].y; y++) {
					float x1 = t.verts[0].x;
					float x2 = (y - b1) / m1;
					if (x1 == x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					}
					else if (x1 < x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					} else if (x2 < x1) {
						//drawLine(x2, x1, y, y, 0, y, c);
						shadeLine(x2, x1, y, y, 0, y, t, orig);
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
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					}
					else if (x1 < x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					} else if (x2 < x1) {
						//drawLine(x2, x1, y, y, 0, y, c);
						shadeLine(x2, x1, y, y, 0, y, t, orig);
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
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					}
					else if (x1 < x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					} else if (x2 < x1) {
						//drawLine(x2, x1, y, y, 0, y, c);
						shadeLine(x2, x1, y, y, 0, y, t, orig);
					}

				}
			}

		}

		void ftTrig(Trig t, char c, Trig orig) {
			if (t.verts[2].x - t.verts[0].x == 0.0f) {
				float m1 = (t.verts[2].y - t.verts[1].y) / (t.verts[2].x - t.verts[1].x);
				float b1 = t.verts[2].y - (m1*t.verts[2].x);
				for (int y = t.verts[2].y; y >= t.verts[0].y; y--) {
					float x1 = t.verts[0].x;
					float x2 = (y - b1) / m1;
					if (x1 == x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					}
					else if (x1 < x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					} else if (x2 < x1) {
						//drawLine(x2, x1, y, y, 0, y, c);
						shadeLine(x2, x1, y, y, 0, y, t, orig);
					}

				}
			}
			else if (t.verts[2].x - t.verts[1].x == 0.0f) {
				float m2 = (t.verts[2].y - t.verts[0].y) / (t.verts[2].x - t.verts[0].x);
				float b2 = t.verts[2].y - (m2*t.verts[2].x);
				for (int y = t.verts[2].y; y >= t.verts[0].y; y--) {
					float x1 = t.verts[1].x;
					float x2 = (y - b2) / m2;
					if (x1 == x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					}
					else if (x1 < x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					} else if (x2 < x1) {
						//drawLine(x2, x1, y, y, 0, y, c);
						shadeLine(x2, x1, y, y, 0, y, t, orig);
					}

				}
			} else {
				float m1 = (t.verts[2].y - t.verts[1].y) / (t.verts[2].x - t.verts[1].x);
				float b1 = t.verts[2].y - (m1*t.verts[2].x);
				float m2 = (t.verts[2].y - t.verts[0].y) / (t.verts[2].x - t.verts[0].x);
				float b2 = t.verts[2].y - (m2*t.verts[2].x);
				for (int y = t.verts[2].y; y >= t.verts[0].y; y--) {
					float x1 = (y - b1) / m1;
					float x2 = (y - b2) / m2;
					if (x1 == x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					}
					else if (x1 < x2) {
						//drawLine(x1, x2, y, y, 0, y, c);
						shadeLine(x1, x2, y, y, 0, y, t, orig);
					} else if (x2 < x1) {
						//drawLine(x2, x1, y, y, 0, y, c);
						shadeLine(x2, x1, y, y, 0, y, t, orig);
					}

				}
			}

		}

		void fillTrig(Trig t, char c) {
			std::sort(t.verts, t.verts + 3, [](Vert const& a, Vert const& b) -> bool {
					return a.y < b.y;
					});
			if(t.verts[1].y == t.verts[2].y) {
				fbTrig(t, c, t);
				std::cout << t.verts[0].x << " " << t.verts[0].y << std::endl;
				std::cout << t.verts[1].x << " " << t.verts[1].y << std::endl;
				std::cout << t.verts[2].x << " " << t.verts[2].y << std::endl;
			} else if (t.verts[0].y == t.verts[1].y) {
				ftTrig(t, c, t);
			} else {
				std::cout << t.verts[0].x << " " << t.verts[0].y << std::endl;
				std::cout << t.verts[1].x << " " << t.verts[1].y << std::endl;
				std::cout << t.verts[2].x << " " << t.verts[2].y << std::endl;
				float m1 = (t.verts[0].y - t.verts[2].y) / (t.verts[0].x - t.verts[2].x);
				float b1 = t.verts[0].y - (m1*t.verts[0].x);
				float nX = (t.verts[1].y - b1) / m1;
				Vert a(t.verts[0].x, t.verts[0].y, t.verts[0].z, t.verts[0].c);
				Vert b(t.verts[1].x, t.verts[1].y, t.verts[1].z, t.verts[1].c);
				Vert cc(nX, t.verts[1].y, t.verts[1].z, 1.0f);
				Vert d(t.verts[2].x, t.verts[2].y, t.verts[2].z, t.verts[2].c);
				Trig fb(a, b, cc);
				//std::cout << t.verts[2].c << std::endl;
				fbTrig(fb, c, t);
				Trig ft(b, cc, d);
				ftTrig(ft, c, t);
			}
		}

};

int main() {

	Screen screen(gScreenWidth, gScreenHeight, ' ');
	Vert p1(50.f, 10.f, -30.0f, 1.0f);
	Vert p2(75.0f, 20.0f, -30.0f, 0.1f);
	Vert p3(40.f, 20.f, -30.0f, 0.1f);
	float rotA = 45.f;
	Trig t1(p1, p2, p3);

	float rotz[4][4];
	rotz[0][0] = cosf(rotA);
	rotz[0][1] = sinf(rotA);
	rotz[0][2] = 0.0f;
	rotz[0][3] = 0.0f;

	rotz[1][0] = -sinf(rotA);
	rotz[1][1] = cosf(rotA);
	rotz[1][2] = 0.0f;
	rotz[1][3] = 0.0f;

	rotz[2][0] = 0.0f;
	rotz[2][1] = 0.0f;
	rotz[2][2] = 1.0f;
	rotz[2][3] = 0.0f;

	rotz[3][0] = 0.0f;
	rotz[3][1] = 0.0f;
	rotz[3][2] = 0.0f;
	rotz[3][3] = 1.0f;

	Vert r1, r2, r3;

	r1.x = t1.verts[0].x * rotz[0][0] + t1.verts[0].y * rotz[1][0] + t1.verts[0].z * rotz[2][0] + rotz[3][0];
	r1.y = t1.verts[0].x * rotz[0][1] + t1.verts[0].y * rotz[1][1] + t1.verts[0].z * rotz[2][1] + rotz[3][1];
	r1.z = t1.verts[0].x * rotz[0][2] + t1.verts[0].y * rotz[1][2] + t1.verts[0].z * rotz[2][2] + rotz[3][2];
	float w = t1.verts[0].x * rotz[0][3] + t1.verts[0].y * rotz[1][3] + t1.verts[0].z * rotz[2][3] + rotz[3][3];

	if (w != 0.0f) {
		r1.x /= w;
		r1.y /= w;
		r1.z /= w;
	}

	r2.x = t1.verts[1].x * rotz[0][0] + t1.verts[1].y * rotz[1][0] + t1.verts[1].z * rotz[2][0] + rotz[3][0];
	r2.y = t1.verts[1].x * rotz[0][1] + t1.verts[1].y * rotz[1][1] + t1.verts[1].z * rotz[2][1] + rotz[3][1];
	r2.z = t1.verts[1].x * rotz[0][2] + t1.verts[1].y * rotz[1][2] + t1.verts[1].z * rotz[2][2] + rotz[3][2];
	w = t1.verts[1].x * rotz[0][3] + t1.verts[1].y * rotz[1][3] + t1.verts[1].z * rotz[2][3] + rotz[3][3];

	if (w != 0.0f) {
		r2.x /= w;
		r2.y /= w;
		r2.z /= w;
	}

	r3.x = t1.verts[2].x * rotz[0][0] + t1.verts[2].y * rotz[1][0] + t1.verts[2].z * rotz[2][0] + rotz[3][0];
	r3.y = t1.verts[2].x * rotz[0][1] + t1.verts[2].y * rotz[1][1] + t1.verts[2].z * rotz[2][1] + rotz[3][1];
	r3.z = t1.verts[2].x * rotz[0][2] + t1.verts[2].y * rotz[1][2] + t1.verts[2].z * rotz[2][2] + rotz[3][2];
	w = t1.verts[2].x * rotz[0][3] + t1.verts[2].y * rotz[1][3] + t1.verts[2].z * rotz[2][3] + rotz[3][3];

	if (w != 0.0f) {
		r3.x /= w;
		r3.y /= w;
		r3.z /= w;
	}

	Trig t3(r1, r2, r3);

	int aspect = gScreenWidth / gScreenHeight;
	float fov = 0.785398f;
	float zn = 0.1f;
	float zf = 100.f;

	float pers[4][4];
	pers[0][0] = 1 / (aspect * tan(fov/2));
	pers[0][1] = 0.0f;
	pers[0][2] = 0.0f;
	pers[0][3] = 0.0f;

	pers[1][0] = 0.0f;
	pers[1][1] = 1 / tan(fov/2);
	pers[1][2] = 0.0f;
	pers[1][3] = 0.0f;

	pers[2][0] = 0.0f;
	pers[2][1] = 0.0f;
	pers[2][2] = - ((zf + zn) / (zf - zn));
	pers[2][3] = - ((2 * zf * zn) / (zf-zn));

	pers[3][0] = 0.0f;
	pers[3][1] = 0.0f;
	pers[3][2] = -1.f;
	pers[3][3] = 0.0f;

	Vert a1, b2, c1;

	a1.x = t3.verts[0].x * pers[0][0] + t3.verts[0].y * pers[1][0] + t3.verts[0].z * pers[2][0] + pers[3][0];
	a1.y = t3.verts[0].x * pers[0][1] + t3.verts[0].y * pers[1][1] + t3.verts[0].z * pers[2][1] + pers[3][1];
	a1.z = t3.verts[0].x * pers[0][2] + t3.verts[0].y * pers[1][2] + t3.verts[0].z * pers[2][2] + pers[3][2];
	w = t3.verts[0].x * pers[0][3] + t3.verts[0].y * pers[1][3] + t3.verts[0].z * pers[2][3] + pers[3][3];

	if (w != 0.0f) {
		a1.x /= w;
		a1.y /= w;
		a1.z /= w;
	}

	b2.x = t3.verts[1].x * pers[0][0] + t3.verts[1].y * pers[1][0] + t3.verts[1].z * pers[2][0] + pers[3][0];
	b2.y = t3.verts[1].x * pers[0][1] + t3.verts[1].y * pers[1][1] + t3.verts[1].z * pers[2][1] + pers[3][1];
	b2.z = t3.verts[1].x * pers[0][2] + t3.verts[1].y * pers[1][2] + t3.verts[1].z * pers[2][2] + pers[3][2];
	w = t3.verts[1].x * pers[0][3] + t3.verts[1].y * pers[1][3] + t3.verts[1].z * pers[2][3] + pers[3][3];

	if (w != 0.0f) {
		b2.x /= w;
		b2.y /= w;
		b2.z /= w;
	}

	c1.x = t3.verts[2].x * pers[0][0] + t3.verts[2].y * pers[1][0] + t3.verts[2].z * pers[2][0] + pers[3][0];
	c1.y = t3.verts[2].x * pers[0][1] + t3.verts[2].y * pers[1][1] + t3.verts[2].z * pers[2][1] + pers[3][1];
	c1.z = t3.verts[2].x * pers[0][2] + t3.verts[2].y * pers[1][2] + t3.verts[2].z * pers[2][2] + pers[3][2];
	w = t3.verts[2].x * pers[0][3] + t3.verts[2].y * pers[1][3] + t3.verts[2].z * pers[2][3] + pers[3][3];

	if (w != 0.0f) {
		c1.x /= w;
		c1.y /= w;
		c1.z /= w;
	}



	Trig t2(a1, b2, c1);

	float slope = 0.1f;
	while (1) {
		std::system("clear");
		//screen.drawTrig(t1, 'o');
		screen.fillTrig(t2, '*');
		screen.print();
		screen.clear();
		slope += 0.001f;
	}

	return 0;
}
