
float near = 0.1f;
float far = 9.9f;

glm::mat4 fov_perspective(float aspect, float fov_deg)
{
	return glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::perspective(glm::radians(fov_deg), aspect, near, far);
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a) {
	return fov_perspective(a, 90);
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
	return fov_perspective(a, 120);
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
	return fov_perspective(a, 30);
}

// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
	
	float tan_fov_half = glm::tan(glm::radians(45.0f));

	float l = -a * near * tan_fov_half;
	float r = 0;
	float b = - near * tan_fov_half;
	float t = near * tan_fov_half;

	return glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::frustum(l, r, b, t, near, far);
}

