#include "Mesh.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>

/* Default constructor - create a vertex with NO normal
 * @param xx: x position
 * @param yy: y position
 * @param zz: z position */
Vert::Vert(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
	xn = 0.f;
	yn = 0.f;
	zn = 0.f;
}

/* Default constructor - create a vertex WITH a normal
 * @param xx: x position
 * @param yy: y position
 * @param zz: z position
 * @param nx: x normal location
 * @param ny: y normal location
 * @param nz: z normal location */
Vert::Vert(float xx, float yy, float zz, float nx, float ny, float nz) {
	x = xx;
	y = yy;
	z = zz;
	xn = nx;
	yn = ny;
	zn = nz;
}

/* Default constructor - create a vertex
 * Default values: x,y,z, xn,yn,zn = 0 */
Vert::Vert() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	xn = 0.f;
	yn = 0.f;
	zn = 0.f;
}

/* Default constructor - create a triangle
 * @params p1,p2,p3: vertices of the triangle
 * @params x,y,z: the face normal of the triangle */
Trig::Trig(Vert p1, Vert p2, Vert p3, float x, float y, float z) {
	verts[0] = p1;
	verts[1] = p2;
	verts[2] = p3;

	Vert p1n(p1.xn, p1.yn, p1.zn);
	Vert p2n(p2.xn, p2.yn, p2.zn);
	Vert p3n(p3.xn, p3.yn, p3.zn);

	norms[0] = p1n;
	norms[1] = p2n;
	norms[2] = p3n;

	Vert n(x, y, z);
	fNormal = n;
}

/* Default constructor - load an obj file mesh thats smoothed
 * @param s: any random number, doesn't matter - doesn't do anything
 * @param objFile: path to file */
Mesh::Mesh(int s, std::string objFile) {

	std::fstream file;
	std::string index;
	std::string x;
	std::string y;
	std::string z;

	std::string nx, ny, nz;

	std::vector<std::string> vertices;
	std::vector<std::string> normals;

	file.open(objFile);
	while(file >> index) {
		if (index == "v") {
			file >> x;
			file >> y;
			file >> z;
			vertices.push_back(x + " " + y + " " + z);
		} else if (index == "vn") {
			file >> x;
			file >> y;
			file >> z;
			normals.push_back(x + " " + y + " " + z);
		} else if (index == "f") {
			file >> x;
			file >> y;
			file >> z;
			std::replace(x.begin(), x.end(), '/', ' ');
			std::replace(y.begin(), y.end(), '/', ' ');
			std::replace(z.begin(), z.end(), '/', ' ');

			std::istringstream a(x);
			std::istringstream b(y);
			std::istringstream c(z);
			std::string p1, n1, n2, n3;
			std::string p2;
			std::string p3;
			a >> p1 >> n1;
			b >> p2 >> n2;
			c >> p3 >> n3;

			std::istringstream v(vertices[std::stoi(p1)-1]);
			v >> x;
			v >> y;
			v >> z;
			std::istringstream norm1(normals[std::stoi(n1)-1]);
			norm1 >> nx;
			norm1 >> ny;
			norm1 >> nz;
			Vert v1(std::stof(x), std::stof(y), std::stof(z),
					std::stof(nx), std::stof(ny), std::stof(nz));

			std::istringstream vv(vertices[std::stoi(p2)-1]);
			vv >> x;
			vv >> y;
			vv >> z;
			std::istringstream norm2(normals[std::stoi(n2)-1]);
			norm2 >> nx;
			norm2 >> ny;
			norm2 >> nz;
			Vert v2(std::stof(x), std::stof(y), std::stof(z),
					std::stof(nx), std::stof(ny), std::stof(nz));

			std::istringstream vvv(vertices[std::stoi(p3)-1]);
			vvv >> x;
			vvv >> y;
			vvv >> z;
			std::istringstream norm3(normals[std::stoi(n3)-1]);
			norm3 >> nx;
			norm3 >> ny;
			norm3 >> nz;
			Vert v3(std::stof(x), std::stof(y), std::stof(z),
					std::stof(nx), std::stof(ny), std::stof(nz));

			Vert dir1(v2.x-v1.x, v2.y-v1.y, v2.z-v1.z);
			Vert dir2(v3.x-v1.x, v3.y-v1.y, v3.z-v1.z);
			Vert cross((dir1.y*dir2.z)-(dir1.z*dir2.y),
					(dir1.z*dir2.x)-(dir1.x*dir2.z), (dir1.x*dir2.y)-(dir1.y*dir2.x));

			float l = sqrtf(cross.x*cross.x + cross.y*cross.y + cross.z*cross.z);
			cross.x /= l;
			cross.y /= l;
			cross.z /= l;

			Trig t(v1, v2, v3, cross.x, cross.y, cross.z);

			trigs.push_back(t);
		}
	}
}

/* Default constructor - load an obj file mesh (MUST BE FLAT SHADED)
 * @param objFile: path to file */
Mesh::Mesh(std::string objFile) {

	std::fstream file;
	std::string index;
	std::string x;
	std::string y;
	std::string z;

	std::vector<std::string> vertices;
	std::vector<std::string> normals;

	file.open(objFile);
	while(file >> index) {
		if (index == "v") {
			file >> x;
			file >> y;
			file >> z;
			vertices.push_back(x + " " + y + " " + z);
		} else if (index == "vn") {
			file >> x;
			file >> y;
			file >> z;
			normals.push_back(x + " " + y + " " + z);
		} else if (index == "f") {
			file >> x;
			file >> y;
			file >> z;
			std::replace(x.begin(), x.end(), '/', ' ');
			std::replace(y.begin(), y.end(), '/', ' ');
			std::replace(z.begin(), z.end(), '/', ' ');

			std::istringstream a(x);
			std::istringstream b(y);
			std::istringstream c(z);
			std::string p1, n;
			std::string p2;
			std::string p3;
			a >> p1 >> n;
			b >> p2;
			c >> p3;

			std::istringstream v(vertices[std::stoi(p1)-1]);
			v >> x;
			v >> y;
			v >> z;
			Vert v1(std::stof(x), std::stof(y), std::stof(z));

			std::istringstream vv(vertices[std::stoi(p2)-1]);
			vv >> x;
			vv >> y;
			vv >> z;
			Vert v2(std::stof(x), std::stof(y), std::stof(z));

			std::istringstream vvv(vertices[std::stoi(p3)-1]);
			vvv >> x;
			vvv >> y;
			vvv >> z;
			Vert v3(std::stof(x), std::stof(y), std::stof(z));

			std::istringstream norm(normals[std::stoi(n)-1]);
			norm >> x;
			norm >> y;
			norm >> z;
			Trig t(v1, v2, v3, std::stof(x), std::stof(y), std::stof(z));

			trigs.push_back(t);
		}
	}
}

/* Default constructor - Set default translation/rotation amounts */
Mesh::Mesh() {
	transAmt.x = 0.0f;
	transAmt.y = 0.0f;
	transAmt.z = 0.0f;

	rotAmt.x = 0.0f;
	rotAmt.y = 0.0f;
	rotAmt.z = 0.0f;
}

/* Default constructor - creates a simple unit cube. Inherits from mesh */
Cube::Cube() {
	// Front Face
	Vert p1(-1.0f, 1.0f, 1.0f);
	Vert p2(-1.0f, -1.0f, 1.0f);
	Vert p3(1.0f, -1.0f, 1.0f);
	Trig t1(p1, p2, p3, 0.0f, 0.0f, 1.0f);
	Vert p4(1.0f, -1.0f, 1.0f);
	Vert p5(1.0f, 1.0f, 1.0f);
	Vert p6(-1.0f, 1.0f, 1.0f);
	Trig t2(p4, p5, p6, 0.0f, 0.0f, 1.0f);
	// Top Face
	Vert p7(-1.0f, 1.0f, 1.0f);
	Vert p8(1.0f, 1.0f, 1.0f);
	Vert p9(-1.0f, 1.0f, -1.0f);
	Trig t3(p7, p8, p9, 0.0f, 1.0f, 0.0f);
	Vert p10(1.0f, 1.0f, 1.0f);
	Vert p11(1.0f, 1.0f, -1.0f);
	Vert p12(-1.0f, 1.0f, -1.0f);
	Trig t4(p10, p11, p12, 0.0f, 1.0f, 0.0f);
	// Right Face
	Vert p13(1.0f, 1.0f, 1.0f);
	Vert p14(1.0f, -1.0f, 1.0f);
	Vert p15(1.0f, -1.0f, -1.0f);
	Trig t5(p13, p14, p15, 1.0f, 0.0f, 0.0f);
	Vert p16(1.0f, 1.0f, 1.0f);
	Vert p17(1.0f, 1.0f, -1.0f);
	Vert p18(1.0f, -1.0f, -1.0f);
	Trig t6(p16, p17, p18, 1.0f, 0.0f, 0.0f);
	// Left Face
	Vert p19(-1.0f, 1.0f, 1.0f);
	Vert p20(-1.0f, -1.0f, 1.0f);
	Vert p21(-1.0f, -1.0f, -1.0f);
	Trig t7(p19, p20, p21, -1.0f, 0.0f, 0.0f);
	Vert p22(-1.0f, 1.0f, 1.0f);
	Vert p23(-1.0f, 1.0f, -1.0f);
	Vert p24(-1.0f, -1.0f, -1.0f);
	Trig t8(p22, p23, p24, -1.0f, 0.0f, 0.0f);
	// Back Face
	Vert p25(-1.0f, 1.0f, -1.0f);
	Vert p26(-1.0f, -1.0f, -1.0f);
	Vert p27(1.0f, 1.0f, -1.0f);
	Trig t9(p25, p26, p27, 0.0f, 0.0f, -1.0f);
	Vert p28(1.0f, 1.0f, -1.0f);
	Vert p29(1.0f, -1.0f, -1.0f);
	Vert p30(-1.0f, -1.0f, -1.0f);
	Trig t10(p28, p29, p30, 0.0f, 0.0f, -1.0f);
	// Bottom Face
	Vert p31(-1.0f, -1.0f, 1.0f);
	Vert p32(-1.0f, -1.0f, -1.0f);
	Vert p33(1.0f, -1.0f, 1.0f);
	Trig t11(p31, p32, p33, 0.0f, -1.0f, 0.0f);
	Vert p34(1.0f, -1.0f, 1.0f);
	Vert p35(1.0f, -1.0f, -1.0f);
	Vert p36(-1.0f, -1.0f, -1.0f);
	Trig t12(p34, p35, p36, 0.0f, -1.0f, 0.0f);

	trigs = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12};

	transAmt.x = 0.0f;
	transAmt.y = 0.0f;
	transAmt.z = 0.0f;

	rotAmt.x = 0.0f;
	rotAmt.y = 0.0f;
	rotAmt.z = 0.0f;
}
