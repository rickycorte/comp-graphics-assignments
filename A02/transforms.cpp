
// i edited a bit the stating file to call the init function under the matrixes
// in this way i can initialize the matrixes using compiled functions and not macros or hardcoding values
// i also dropped the cost modifier to edit the matrix values

	
// Translate of +2 on the x axis, and -1 on the y axis
float MT1[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};

			
// Rotate of 45 degrees on the x axis
float MT2[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};
			
// Make the object 2 times smaller
float MT3[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};
			
// Make the object 2 times longer on the z axis, and half on the other axis
float MT4[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};

// Mirror over the z axis
float MT5[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};
			
// Flatten over the z axis
float MT6[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};

// Make a shear along the Y axis, with a factor of 1 along the x axis
float MT7[] =  {
			1.0,		0.0,		0.0,		0.0,
			0.0,		1.0,		0.0,		0.0,
			0.0,		0.0,		1.0,		0.0,
			0.0,		0.0,		0.0,		1.0};



void translate(float *matrix, float x, float y, float z) {
	matrix[3] += x;
	matrix[7] += y;
	matrix[11] += z;
}

void rotate_x(float *matrix, float alpha)
{
	matrix[5] = cos(alpha);
	matrix[6] = -sin(alpha);
	matrix[9] = sin(alpha);
	matrix[10] = cos(alpha);
}

void scale(float *matrix, float x, float y, float z)
{
	matrix[0] = x;
	matrix[5] = y;
	matrix[10] = z;
}

void sheer_y(float *matrix, float x, float z)
{
	matrix[1] += x;
	matrix[8] += z;
}

void init_matrices()
{
	translate(MT1, 2, -1, 0);
	rotate_x(MT2, 45 * 0.0174533 /* converto to radiants*/);
	scale(MT3, 0.5, 0.5, 0.5);
	scale(MT4, 0.5, 0.5, 2);
	scale(MT5, -1, -1, 1);
	scale(MT6, 1, 1, 0);
	sheer_y(MT7, 1, 0);
}