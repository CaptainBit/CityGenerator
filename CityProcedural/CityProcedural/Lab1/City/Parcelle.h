#pragma once
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include "..\Dependencies\glm\glm\gtx\transform.hpp"
#include "..\Dependencies\glm\glm\gtc\type_ptr.hpp"
#include "Building.h"

#include <iostream>
#include <vector>
#include <time.h>

enum terrainShape {
	SQUARE , VRECTANGLE, HRECTANGLE
};

class Parcelle
{
public:


	~Parcelle();

	Parcelle(glm::vec3 origin, GLfloat x, GLfloat z, double maxH);

	glm::vec3 originPoint;

	glm::vec3 topRight;


	std::vector <Building> buildings;

	terrainShape premTerrain;

	int nbTerrains;

private:
	void AddBuilding(glm::vec3 highLeft, GLfloat x, GLfloat y, double h);
};

