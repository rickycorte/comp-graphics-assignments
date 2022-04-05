
// Get movement of robot in x,y,z direction
// x is A-D axis
// z is W-S axis
// y is up and is UP-DOWN arrow axis
glm::vec3 getInput(GLFWwindow* window)
{
	glm::vec3 mov = glm::vec3();
	if(glfwGetKey(window, GLFW_KEY_W)) mov.z = -1;
	if (glfwGetKey(window, GLFW_KEY_S)) mov.z = 1;

	if (glfwGetKey(window, GLFW_KEY_D)) mov.x = 1;
	if (glfwGetKey(window, GLFW_KEY_A)) mov.x = -1;

	return mov;
}

const float move_speed = 3.0;

// initialize to infer time automatically
static auto prev_time = std::chrono::high_resolution_clock::now();
static auto current_time = std::chrono::high_resolution_clock::now();

// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {

	static glm::vec3 pos = glm::vec3(-3.0, 0.0, 2.0);

	static glm::quat rotation;

	// compute delta time
	prev_time = current_time; // move current time of old invocation
	current_time = std::chrono::high_resolution_clock::now();
	float delta_time = std::chrono::duration<float, std::chrono::seconds::period>(current_time - prev_time).count();

	// get inputs
	auto move_dir = getInput(window);

	// update position and rotation

	pos += move_dir * move_speed * delta_time;
	// look at rotation only if moved
	if (glm::length(move_dir) != 0) {
		// fix vector horizontal components that are made for movement
		glm::vec3 r = glm::vec3(move_dir.z, move_dir.y, -move_dir.x);
		rotation = glm::quatLookAt(glm::normalize(r), glm::vec3(0, 1, 0));

	}

	// compute output matrix
	glm::mat4 out;

	out = glm::translate(glm::mat4(1.0), pos) * glm::mat4(rotation);

	return out;
}

