#pragma once
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include "..\Dependencies\glm\glm\gtx\transform.hpp"
#include "..\Dependencies\glm\glm\gtc\type_ptr.hpp"

#include <iostream>
#include <vector>
#include <time.h>
#pragma once

class Building
{
public:
	Building(glm::vec3 leftCorner, GLfloat x, GLfloat y, GLfloat z);

	GLfloat height;
	GLfloat width;

	glm::vec3 lowLeft;
	glm::vec3 highRight;

	std::vector <glm::vec3> sommets;

};

