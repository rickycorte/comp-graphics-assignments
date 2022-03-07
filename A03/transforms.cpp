// this is a function body

// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). 
// The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.
glm::mat4 MT1 = glm::mat4(1.0f);

MT1 = glm::translate(MT1, glm::vec3(1.0f, 0.0f, -1.0f));
MT1 = glm::rotate(MT1, glm::radians(-60.0f), glm::vec3(0, 1, 0));
MT1 = glm::rotate(MT1, glm::radians(+30.0f), glm::vec3(0, 0, 1));

MT1 = glm::rotate(MT1, glm::radians(45.0f), glm::vec3(1, 0, 0));

MT1 = glm::rotate(MT1, glm::radians(-30.0f), glm::vec3(0, 0, 1));
MT1 = glm::rotate(MT1, glm::radians(+60.0f), glm::vec3(0, 1, 0));
MT1 = glm::translate(MT1, glm::vec3(-1.0f, 0.0f, 1.0f));

			   
// Half the size of an object, using as fixed point (5,0,-2)
glm::mat4 MT2 = glm::mat4(1);
MT2 = glm::translate(MT2, glm::vec3(5.0f, 0.0f, -2.0f));
MT2 = glm::scale(MT2, 0.5f * glm::vec3(1.0f));
MT2 = glm::translate(MT2, glm::vec3(-5.0f, 0.0f, 2.0f));
			   
// Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane
glm::mat4 MT3 = glm::mat4(1);

MT3 = glm::translate(MT3, glm::vec3(1.0f, 1.0f, 1.0f));
MT3 = glm::rotate(MT3, glm::radians(15.0f), glm::vec3(1, 0, 0));

MT3 = glm::scale(MT3,glm::vec3(1.0f, -1.0f, 1.0f));

MT3 = glm::rotate(MT3, glm::radians(-15.0f), glm::vec3(1, 0, 0));
MT3 = glm::translate(MT3, glm::vec3(-1.0f, -1.0f, -1.0f));
			   
// Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5) then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.
glm::mat4 MT4 = glm::mat4(1);

MT4 = glm::translate(MT4, glm::vec3(0.0f, 0.0f, -5.0f));
MT4 = glm::rotate(MT4, glm::radians(-30.0f), glm::vec3(0, 1, 0));
MT4 = glm::scale(MT4, glm::vec3(1.0f / 3.0f));



