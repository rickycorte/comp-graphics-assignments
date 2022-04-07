#define PI 3.14159

void putVertex(std::vector<tinyobj::real_t>& verts, int index, float x, float y, float z)
{
	verts[index * 3] = x;
	verts[index * 3 + 1] = y;
	verts[index * 3 + 2] = z;

}

void make_cube() {
	M1_vertices.resize(3 * 8);

	// first vertex of M1

	putVertex(M1_vertices, 0, -1, -1, -1);
	putVertex(M1_vertices, 1, 1, -1, -1);
	putVertex(M1_vertices, 2, 1, 1, -1);
	putVertex(M1_vertices, 3, -1, 1, -1);

	putVertex(M1_vertices, 4, -1, -1, 1);
	putVertex(M1_vertices, 5, 1, -1, 1);
	putVertex(M1_vertices, 6, 1, 1, 1);
	putVertex(M1_vertices, 7, -1, 1, 1);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 2);

	M1_indices = {
		// front
		0,1,2,
		2,3,0,
		//top
		2,6,3,
		6,7,3,
		//bot
		0,4,1,
		1,4,5,
		//left
		0,4,3,
		3,7,4,
		//right
		1,5,2,
		2,6,5,
		//back
		4,5,6,
		6,7,4,
	};
}

void make_cylinder() {
	float h = 2;
	int cyl_slices = 20;

	M2_vertices.resize(4 * 3);
	putVertex(M2_vertices, 0, 0, 0, 0); // top center
	putVertex(M2_vertices, 1, 0, h, 0); //bot center
	int offset = 2;

	//first slice
	putVertex(M2_vertices, 2, 1, 0, 0); // cos (0), sin(0)
	putVertex(M2_vertices, 3, 1, h, 0); // cos (0), sin(0)

	float step = 2.0 * PI / (float)cyl_slices;
	for (int i = 1; i <= cyl_slices; i++) {
		// push vertices for slice
		M2_vertices.push_back(glm::cos(i * step));
		M2_vertices.push_back(0);
		M2_vertices.push_back(glm::sin(i * step));

		M2_vertices.push_back(glm::cos(i * step));
		M2_vertices.push_back(h);
		M2_vertices.push_back(glm::sin(i * step));

		int idx = i % cyl_slices; // alows to close the circle without special case

		// bottom triangle
		M2_indices.push_back(0);
		M2_indices.push_back(offset + idx * 2);
		M2_indices.push_back(offset + (i - 1) * 2);

		// square
		M2_indices.push_back(offset + idx * 2);
		M2_indices.push_back(offset + idx * 2 + 1);
		M2_indices.push_back(offset + (i - 1) * 2);

		M2_indices.push_back(offset + idx * 2 + 1);
		M2_indices.push_back(offset + (i - 1) * 2 + 1);
		M2_indices.push_back(offset + (i - 1) * 2);


		// top trinagle
		M2_indices.push_back(1);
		M2_indices.push_back(offset + idx * 2 + 1);
		M2_indices.push_back(offset + (i - 1) * 2 + 1);

	}

}

void make_sphere() {
	float r = 0.5f;
	int m = 10; // divisions of a vertical slice (add 2 to the desider quantity)
	int n = 10; // slice around

	//create vertexes from top to bottom for every line
	for (int i = 0; i < n; i++) {
		float hor = 2 * PI * (float)i / (float)n;

		for (int j = 0; j <= m; j++) { // slip poles
			float vert = PI * (float)j / (float)m;

			M3_vertices.push_back(r * glm::cos(hor) * glm::sin(vert));
			M3_vertices.push_back(r * glm::cos(vert));
			M3_vertices.push_back(r * glm::sin(hor) * glm::sin(vert));
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
	int steps = 15; // steps for every round (360 rotation)
	float round_height = 0.5f;

	int tube_faces = 15;

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
			M4_vertices.push_back(waypoint_x + tube_radius * glm::cos(angle) * glm::sin(j * face_step));
			M4_vertices.push_back(height + tube_radius * glm::cos(j * face_step));
			M4_vertices.push_back(waypoint_z + tube_radius * glm::sin(angle) * glm::sin(j * face_step));
		}

		angle += delta_angle;
		height += delta_step;
	}

	for (int i = 1; i < rounds * steps; i++) {
		for (int j = 0; j < tube_faces; j++) {
			float next_face = (j + 1) % tube_faces;

			M4_indices.push_back(i * tube_faces + j);
			M4_indices.push_back((i - 1) * tube_faces + j);
			M4_indices.push_back(i * tube_faces + next_face);

			M4_indices.push_back((i - 1) * tube_faces + j);
			M4_indices.push_back(i * tube_faces + next_face);
			M4_indices.push_back((i - 1) * tube_faces + next_face);


		}
	}
}

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {

	make_cube();

	make_cylinder();

	make_sphere();

	make_spring();

}
