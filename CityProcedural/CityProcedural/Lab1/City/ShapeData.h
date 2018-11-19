#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include "..\Dependencies\glm\glm\gtx\transform.hpp"
#include "..\Dependencies\glm\glm\gtc\type_ptr.hpp"
#include <vector>
#include <iostream>
#include "Parcelle.h"
#include "Building.h"
#pragma once


class ShapeData
{
public:
	ShapeData();
	void MakeBase(Building building);
	void MakeFloor(glm::vec3 lowLeft, glm::vec3 highRight, float y, int iter);
private:
	int X;
	int Y;

	GLuint _indice;


	GLfloat RandomColor();
};


