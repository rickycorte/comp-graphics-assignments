// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

#define PI 3.14159

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;

void make_cube() {

	// this is really ugly, but...
	// never spent 10 hours faling to automate a task
	// when you can do it manually in 10 minuts

	// top face (3)
	Vertex V1{ glm::vec3(-1, 1, -1), glm::vec3(0,1,0), glm::vec2(0, 0.375)};
	M1_vertices.push_back(V1);
	Vertex V2{ glm::vec3(1, 1, -1), glm::vec3(0,1,0), glm::vec2(0, 0.25)};
	M1_vertices.push_back(V2);
	Vertex V3{ glm::vec3(-1, 1, 1), glm::vec3(0,1,0), glm::vec2(0.125, 0.375)};
	M1_vertices.push_back(V3);
	Vertex V4{ glm::vec3(1, 1, 1), glm::vec3(0,1,0), glm::vec2(0.125, 0.25)};
	M1_vertices.push_back(V4);

	// bottom face (4)
	Vertex V5{ glm::vec3(-1, -1, -1), glm::vec3(0,-1,0), glm::vec2(0.375, 0.375) };
	M1_vertices.push_back(V5);
	Vertex V6{ glm::vec3(1, -1, -1), glm::vec3(0,-1,0), glm::vec2(0.375, 0.25) };
	M1_vertices.push_back(V6);
	Vertex V7{ glm::vec3(-1, -1, 1), glm::vec3(0,-1,0), glm::vec2(0.25, 0.375) };
	M1_vertices.push_back(V7);
	Vertex V8{ glm::vec3(1, -1, 1), glm::vec3(0,-1,0), glm::vec2(0.25, 0.25) };
	M1_vertices.push_back(V8);

	// front (1)
	Vertex V9{ glm::vec3(-1, -1, -1), glm::vec3(0,0,0 - 1), glm::vec2(0.25, 0)};
	M1_vertices.push_back(V9);
	Vertex V10{ glm::vec3(1, -1, -1), glm::vec3(0,0,-1), glm::vec2(0.25, 0.125) };
	M1_vertices.push_back(V10);
	Vertex V11{ glm::vec3(-1, 1, -1), glm::vec3(0,0,-1), glm::vec2(0.125, 0)};
	M1_vertices.push_back(V11);
	Vertex V12{ glm::vec3(1, 1, -1), glm::vec3(0,0,-1), glm::vec2(0.125, 0.125) };
	M1_vertices.push_back(V12);

	// front (6)
	Vertex V13{ glm::vec3(-1, -1, 1), glm::vec3(0,0,+1), glm::vec2(0.25, 0.375)};
	M1_vertices.push_back(V13);
	Vertex V14{ glm::vec3(1, -1, 1), glm::vec3(0,0,1), glm::vec2(0.25, 0.25)};
	M1_vertices.push_back(V14);
	Vertex V15{ glm::vec3(-1, 1, 1), glm::vec3(0,0,1), glm::vec2(0.125, 0.375)};
	M1_vertices.push_back(V15);
	Vertex V16{ glm::vec3(1, 1, 1), glm::vec3(0,0,1), glm::vec2(0.125, 0.25)};
	M1_vertices.push_back(V16);

	// back (5)
	Vertex V17{ glm::vec3(-1, -1, -1), glm::vec3(-1,0,0), glm::vec2(0.25, 0.5) };
	M1_vertices.push_back(V17);
	Vertex V18{ glm::vec3(-1, +1, -1), glm::vec3(-1,0,0), glm::vec2(0.125, 0.5)};
	M1_vertices.push_back(V18);
	Vertex V19{ glm::vec3(-1, -1, 1), glm::vec3(-1,0,0), glm::vec2(0.25, 0.375) };
	M1_vertices.push_back(V19);
	Vertex V20{ glm::vec3(-1, 1, 1), glm::vec3(-1,0,0), glm::vec2(0.125, 0.375) };
	M1_vertices.push_back(V20);

	//back (2)
	Vertex V21{ glm::vec3(1, -1, -1), glm::vec3(1,0,0), glm::vec2(0.25, 0.125)};
	M1_vertices.push_back(V21);
	Vertex V22{ glm::vec3(1, 1, -1), glm::vec3(1,0,0), glm::vec2(0.125, 0.125)};
	M1_vertices.push_back(V22);
	Vertex V23{ glm::vec3(1, -1, 1), glm::vec3(1,0,0), glm::vec2(0.25, 0.25) };
	M1_vertices.push_back(V23);
	Vertex V24{ glm::vec3(1, 1, 1), glm::vec3(1,0,0), glm::vec2(0.125, 0.25) };
	M1_vertices.push_back(V24);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 12);

	M1_indices = {
		//top face
		0,1,2,
		1,2,3,
		// bottom,
		4,5,6,
		5,6,7,
		//front
		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,
		//back
		16,17,18,
		17,18,19,

		20,21,22,
		21,22,23,
	};
}

glm::vec2 cy_uv_center_up = glm::vec2(0.625, 0.125);
glm::vec2 cy_uv_center_down = glm::vec2(0.875, 0.125);
glm::vec2 cy_uv_rect_top = glm::vec2(0.5, 0.25);
float cy_uv_r = 0.125f;
float cy_uv_len = 0.5;
float cy_uv_h = 0.25;

void add_cylinder_slice(float angle, float height, float uv_step_perc, float radius = 1) {
	// insert order for a slice: normal down (bot) -> normal face (bot) -> normal face (up) -> normal up (up)
	float x = glm::cos(angle);
	float z = glm::sin(angle);

	Vertex V1up{ glm::vec3(x * radius, 0, z * radius), glm::vec3(0,-1,0), cy_uv_center_down + glm::vec2(x,z) * cy_uv_r};
	Vertex V1f{ glm::vec3(x * radius,0, z * radius), glm::vec3(x, 0, z), cy_uv_rect_top + glm::vec2(cy_uv_len * uv_step_perc, cy_uv_h)};
	M2_vertices.push_back(V1up);
	M2_vertices.push_back(V1f);

	Vertex V2f{ glm::vec3(x * radius,height, z * radius), glm::vec3(x, 0, z), cy_uv_rect_top + glm::vec2(cy_uv_len * uv_step_perc, 0) }; 
	Vertex V2down{ glm::vec3(x * radius,height,z * radius), glm::vec3(0,1,0),  cy_uv_center_up + glm::vec2(x,z) * cy_uv_r };
	M2_vertices.push_back(V2f);
	M2_vertices.push_back(V2down);
}

void make_cylinder() {
	float h = 2;
	int cyl_slices = 30;

	//M2_vertices.resize(4 * 3);
	Vertex bottom{ glm::vec3(0, 0, 0), glm::vec3(0, -1, 0), cy_uv_center_down };
	Vertex top{ glm::vec3(0,h,0), glm::vec3(0,1,0), cy_uv_center_up};
	M2_vertices.push_back(bottom);
	M2_vertices.push_back(top);

	int offset = 2;

	//first slice
	add_cylinder_slice(0, h, 0);

	float step = 2.0 * PI / (float)cyl_slices;
	for (int i = 1; i <= cyl_slices; i++) {
		float uv_perc = (float)i / (float)cyl_slices;
		// push vertices for slice
		add_cylinder_slice(i * step, h, uv_perc);

		int idx = i; // alows to close the circle without special case

		// bottom triangle
		M2_indices.push_back(0);
		M2_indices.push_back(offset + idx * 4);
		M2_indices.push_back(offset + (i - 1) * 4);

		// square
		M2_indices.push_back(offset + idx * 4 + 1);
		M2_indices.push_back(offset + idx * 4 + 2); // up
		M2_indices.push_back(offset + (i - 1) * 4 + 1); // back

		M2_indices.push_back(offset + idx * 4 + 2); // up
		M2_indices.push_back(offset + (i - 1) * 4 + 2); // up back
		M2_indices.push_back(offset + (i - 1) * 4 + 1); // down back


		// top trinagle
		M2_indices.push_back(1);
		M2_indices.push_back(offset + idx * 4 + 3);
		M2_indices.push_back(offset + (i - 1) * 4 + 3);

	}

}


void makeModels() {

	make_cube();

	make_cylinder();

}