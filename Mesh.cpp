#include "Mesh.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

/* Default constructor
 * @param xx our x position
 * @param yy our y position
 * @param zz our z position */
Vert::Vert(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
}

/* Default constructor - create a vertex
 * @param xx our x position
 * @param yy our y position
 * @param zz our z position
 * @param nx our x normal location
 * @param ny our y normal location
 * @param nz our z normal location */
Vert::Vert(float xx, float yy, float zz, float nx, float ny, float nz) {
	x = xx;
	y = yy;
	z = zz;
	xn = nx;
	yn = ny;
	zn = nz;
}

/* Default constructor - create a vertex
 * Default values: x,y,z = 0 */
Vert::Vert() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/* Default constructor
 * @params p1,p2,p3 vertices of the triangle
 * @params x,y,z the face normal of the triangle */
Trig::Trig(Vert p1, Vert p2, Vert p3, float x, float y, float z) {
	verts[0] = p1;
	verts[1] = p2;
	verts[2] = p3;

	Vert n(x, y, z);
	fNormal = n;
}

/* Default constructor - load an obj file mesh */
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

			//std::cout << t.verts[0].x << ", " << t.verts[0].y << ", " << t.verts[0].z << std::endl;

			//std::cout << p1 << " " << p2 << " " << p3 << std::endl;
			//std::cout << vertices[0] << std::endl;
			//std::cout << v3.x << std::endl;
		}
	}

	std::istringstream v(vertices[0]);
	v >> x;
	//std::cout << normals[0] << std::endl;

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
