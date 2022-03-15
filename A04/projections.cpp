
float near = -4.0f;
float far = 12.0f;
float w = 4.0f;


// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a) {
	auto parallel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::ortho(-w, w, -w / a, w / a, near, far);
	auto x_rot_35 = glm::rotate(glm::mat4(1.0f), glm::radians(35.26f), glm::vec3(1, 0, 0));
	auto y_rot_45 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 1, 0));
	glm::mat4 out = parallel * x_rot_35 * y_rot_45;
	return out;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
	float alpha = glm::radians(45.0f);

	auto parallel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::ortho(-w, w, -w / a, w / a, near, far);
	auto x_rot_alpha = glm::rotate(glm::mat4(1.0f), alpha, glm::vec3(1, 0, 0));
	auto y_rot_45 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 1, 0));
	glm::mat4 out = parallel * x_rot_alpha * y_rot_45;
	return out;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
	float alpha = glm::radians(45.0f);
	float beta = glm::radians(60.0f);

	auto parallel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::ortho(-w, w, -w / a, w / a, near, far);
	auto x_rot_alpha = glm::rotate(glm::mat4(1.0f), alpha, glm::vec3(1, 0, 0));
	auto y_rot_45 = glm::rotate(glm::mat4(1.0f), beta, glm::vec3(0, 1, 0));
	glm::mat4 out = parallel * x_rot_alpha * y_rot_45;
	return out;
}

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a) {
	auto parallel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::ortho(-w, w, -w / a, w / a, near, far);
	auto sheer = glm::mat4(1.0f);
	sheer[2][0] = -0.5f * glm::cos(glm::radians(45.0f));
	sheer[2][1] = -0.5f * glm::sin(glm::radians(45.0f));

	return parallel * sheer;
}

