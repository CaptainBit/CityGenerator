#pragma once
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include "..\Dependencies\glm\glm\gtx\transform.hpp"
#include "..\Dependencies\glm\glm\gtc\type_ptr.hpp"

#include <iostream>
#include <vector>

#include <random>

#include "Parcelle.h"

#define WIDTH 1.0f
#define HEIGHT 1.0f

class GridMaker
{
public:
	GridMaker(int scale);

	~GridMaker();

	std::vector <Parcelle> parcelles;

	glm::vec3 lowLeft;
	glm::vec3 highRight;

private:

	std::vector <double> kernel;
	void getGaussianKernel(int rows, int cols, double sigmax, double sigmay);

};

