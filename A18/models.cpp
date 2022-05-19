// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

#define PI 3.14159


struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

// vertex is pos, norm

void make_cube() {

	// this is really ugly, but...
	// never spent 10 hours faling to automate a task
	// when you can do it manually in 10 minuts

	// top face
	Vertex V1{ glm::vec3(-1, 1, -1), glm::vec3(0,1,0)};
	M1_vertices.push_back(V1);
	Vertex V2{ glm::vec3(1, 1, -1), glm::vec3(0,1,0) };
	M1_vertices.push_back(V2);
	Vertex V3{ glm::vec3(-1, 1, 1), glm::vec3(0,1,0) };
	M1_vertices.push_back(V3);
	Vertex V4{ glm::vec3(1, 1, 1), glm::vec3(0,1,0) };
	M1_vertices.push_back(V4);

	// bottom face
	Vertex V5{ glm::vec3(-1, -1, -1), glm::vec3(0,-1,0) };
	M1_vertices.push_back(V5);
	Vertex V6{ glm::vec3(1, -1, -1), glm::vec3(0,-1,0) };
	M1_vertices.push_back(V6);
	Vertex V7{ glm::vec3(-1, -1, 1), glm::vec3(0,-1,0) };
	M1_vertices.push_back(V7);
	Vertex V8{ glm::vec3(1, -1, 1), glm::vec3(0,-1,0) };
	M1_vertices.push_back(V8);

	// front
	Vertex V9{ glm::vec3(-1, -1, -1), glm::vec3(0,0,0-1) };
	M1_vertices.push_back(V9);
	Vertex V10{ glm::vec3(1, -1, -1), glm::vec3(0,0,-1) };
	M1_vertices.push_back(V10);
	Vertex V11{ glm::vec3(-1, 1, -1), glm::vec3(0,0,-1) };
	M1_vertices.push_back(V11);
	Vertex V12{ glm::vec3(1, 1, -1), glm::vec3(0,0,-1) };
	M1_vertices.push_back(V12);

	Vertex V13{ glm::vec3(-1, -1, 1), glm::vec3(0,0,+1) };
	M1_vertices.push_back(V13);
	Vertex V14{ glm::vec3(1, -1, 1), glm::vec3(0,0,1) };
	M1_vertices.push_back(V14);
	Vertex V15{ glm::vec3(-1, 1, 1), glm::vec3(0,0,1) };
	M1_vertices.push_back(V15);
	Vertex V16{ glm::vec3(1, 1, 1), glm::vec3(0,0,1) };
	M1_vertices.push_back(V16);

	// back
	Vertex V17{ glm::vec3(-1, -1, -1), glm::vec3(-1,0,0) };
	M1_vertices.push_back(V17);
	Vertex V18{ glm::vec3(-1, +1, -1), glm::vec3(-1,0,0) };
	M1_vertices.push_back(V18);
	Vertex V19{ glm::vec3(-1, -1, 1), glm::vec3(-1,0,0) };
	M1_vertices.push_back(V19);
	Vertex V20{ glm::vec3(-1, 1, 1), glm::vec3(-1,0,0) };
	M1_vertices.push_back(V20);

	Vertex V21{ glm::vec3(1, -1, -1), glm::vec3(1,0,0) };
	M1_vertices.push_back(V21);
	Vertex V22{ glm::vec3(1, 1, -1), glm::vec3(1,0,0) };
	M1_vertices.push_back(V22);
	Vertex V23{ glm::vec3(1, -1, 1), glm::vec3(1,0,0) };
	M1_vertices.push_back(V23);
	Vertex V24{ glm::vec3(1, 1, 1), glm::vec3(1,0,0) };
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

void add_cylinder_slice(float angle, float height, float radius = 1) {
	// insert order for a slice: normal down (bot) -> normal face (bot) -> normal face (up) -> normal up (up)
	float x = glm::cos(angle);
	float z = glm::sin(angle);

	Vertex V1up{ glm::vec3(x * radius, 0, z * radius), glm::vec3(0,-1,0) };
	Vertex V1f{ glm::vec3(x * radius,0, z * radius), glm::vec3(x, 0, z) };
	M2_vertices.push_back(V1up);
	M2_vertices.push_back(V1f);

	Vertex V2f{ glm::vec3(x * radius,height, z * radius), glm::vec3(x, 0, z) }; // cos (0), sin(0)
	Vertex V2down{ glm::vec3(x * radius,height,z * radius), glm::vec3(0,1,0) };
	M2_vertices.push_back(V2f);
	M2_vertices.push_back(V2down);
}

void make_cylinder() {
	float h = 2;
	int cyl_slices = 30;

	//M2_vertices.resize(4 * 3);
	Vertex bottom{ glm::vec3(0, 0, 0), glm::vec3(0, -1, 0) };
	Vertex top{ glm::vec3(0,h,0), glm::vec3(0,1,0) };
	M2_vertices.push_back(bottom);
	M2_vertices.push_back(top);

	int offset = 2;
	
	//first slice
	add_cylinder_slice(0, h);

	float step = 2.0 * PI / (float)cyl_slices;
	for (int i = 1; i <= cyl_slices; i++) {
		// push vertices for slice
		add_cylinder_slice(i * step, h);

		int idx = i % cyl_slices; // alows to close the circle without special case

		// bottom triangle
		M2_indices.push_back(0);
		M2_indices.push_back(offset + idx * 4);
		M2_indices.push_back(offset + (i - 1) * 4);

		// square
		M2_indices.push_back(offset + idx * 4 + 1);
		M2_indices.push_back(offset + idx * 4 + 2); // up
		M2_indices.push_back(offset + (i - 1) * 4+1); // back

		M2_indices.push_back(offset + idx * 4 + 2); // up
		M2_indices.push_back(offset + (i - 1) * 4 + 2); // up back
		M2_indices.push_back(offset + (i - 1) * 4 +1); // down back


		// top trinagle
		M2_indices.push_back(1);
		M2_indices.push_back(offset + idx * 4 + 3);
		M2_indices.push_back(offset + (i - 1) * 4 + 3);

	}

}

void make_sphere() {
	float r = 1.0f;
	int m = 30; // divisions of a vertical slice (add 2 to the desider quantity)
	int n = 30; // slice around

	//create vertexes from top to bottom for every line
	for (int i = 0; i < n; i++) {
		float hor = 2 * PI * (float)i / (float)n;

		for (int j = 0; j <= m; j++) { // slip poles
			float vert = PI * (float)j / (float)m;
			float x = glm::cos(hor) * glm::sin(vert);
			float y = glm::cos(vert);
			float z = glm::sin(hor) * glm::sin(vert);
			Vertex v{ r * glm::vec3(x,y,z), glm::vec3(x,y,z) };
			M3_vertices.push_back(v);
		}
	}


	for (int h = 0; h < n; h++) {
		int curr = h * (m + 1); // +1 for lower pole
		int next = ((h + 1) % n) * (m + 1);

		for (int v = 0; v < m; v++)
		{

			M3_indices.push_back(curr + v);
			M3_indices.push_back(curr + v + 1);
			M3_indices.push_back(next + v);

			M3_indices.push_back(next + v);
			M3_indices.push_back(next + v + 1);
			M3_indices.push_back(curr + v + 1);
		}
	}
}


void make_spring() {

	float radius = 0.5f;
	float tube_radius = 0.1f;


	int rounds = 2;
	int steps = 30; // steps for every round (360 rotation)
	float round_height = 0.5f;

	int tube_faces = 30;

	float angle = 0;
	float height = 0;

	float delta_angle = 2 * PI / (float)steps;
	float delta_step = round_height / (float)steps;

	float face_step = 2 * PI / (float)tube_faces;

	for (int i = 0; i < rounds * steps; i++) {

		float waypoint_x = radius * glm::cos(angle);
		float waypoint_z = radius * glm::sin(angle);

		//generate tube waypoints as circles around the center of the generated line
		for (int j = 0; j < tube_faces; j++) {
			// we image to have a sphere centered in the waypoint and slice it with a x/z angle of `angle` radiants
			float x = glm::cos(angle) * glm::sin(j * face_step);
			float y = glm::cos(j * face_step);
			float z = glm::sin(angle) * glm::sin(j * face_step);

			glm::vec3 pos(waypoint_x + tube_radius * x, height + tube_radius * y, waypoint_z + tube_radius * z );
			glm::vec3 norm(x,y,z);

			Vertex v{ pos, norm };

			M4_vertices.push_back(v);
		}

		angle += delta_angle;
		height += delta_step;
	}

	for (int i = 1; i < rounds * steps; i++) {
		for (int j = 0; j < tube_faces; j++) {
			float next_face = (j + 1) % tube_faces;

			M4_indices.push_back(i * tube_faces + next_face);
			M4_indices.push_back((i - 1) * tube_faces + j);
			M4_indices.push_back(i * tube_faces + j);	

			M4_indices.push_back((i - 1) * tube_faces + next_face);
			M4_indices.push_back((i - 1) * tube_faces + j);
			M4_indices.push_back(i * tube_faces + next_face);
		
		}
	}
}

void makeModels() {

	make_cube();

	make_cylinder();

	make_sphere();

	make_spring();

}