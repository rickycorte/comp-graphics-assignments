#define PI 3.14159

void putVertex(std::vector<tinyobj::real_t>& verts, int index, float x, float y, float z)
{
	verts[index * 3] = x;
	verts[index * 3 + 1] = y;
	verts[index * 3 + 2] = z;

}

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
	//// M1 : Cube
	// Replace the code below, that creates a simple square, with the one to create a cube.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
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

	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	// to construct the cylinder i use vertical slices made of top triangle -> vertical rectangle -> bottom triangle

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




	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
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



//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(3 * 6);

// Vertices definitions
M4_vertices[0]  =  0.0;
M4_vertices[1]  =  1.414;
M4_vertices[2]  = -1.0;
M4_vertices[3]  =  0.0;
M4_vertices[4]  = -1.414;
M4_vertices[5]  = -1.0;
M4_vertices[6]  = -1.0;
M4_vertices[7]  =  0.0;
M4_vertices[8]  = -2.0;
M4_vertices[9]  = -1.0;
M4_vertices[10] =  0.0;
M4_vertices[11] =  0.0;
M4_vertices[12] =  1.0;
M4_vertices[13] =  0.0;
M4_vertices[14] =  0.0;
M4_vertices[15] =  1.0;
M4_vertices[16] =  0.0;
M4_vertices[17] = -2.0;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M4_indices.resize(3 * 8);

// indices definitions
M4_indices[0]  = 0;
M4_indices[1]  = 2;
M4_indices[2]  = 3;
M4_indices[3]  = 1;
M4_indices[4]  = 3;
M4_indices[5]  = 2;
M4_indices[6]  = 0;
M4_indices[7]  = 3;
M4_indices[8]  = 4;
M4_indices[9]  = 1;
M4_indices[10] = 4;
M4_indices[11] = 3;
M4_indices[12] = 0;
M4_indices[13] = 4;
M4_indices[14] = 5;
M4_indices[15] = 1;
M4_indices[16] = 5;
M4_indices[17] = 4;
M4_indices[18] = 0;
M4_indices[19] = 5;
M4_indices[20] = 2;
M4_indices[21] = 1;
M4_indices[22] = 2;
M4_indices[23] = 5;
}