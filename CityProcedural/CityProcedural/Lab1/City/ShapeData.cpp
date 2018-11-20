#include "ShapeData.h"



ShapeData::ShapeData()
{

	_indice = 0;
}

void ShapeData::MakeBase(Building building)
{
	GLuint tab[36]{

			0,1,2,
			1,2,3,
			4,5,6,
			5,6,7,
			2,6,7,
			2,3,7,
			0,4,5,
			0,1,5,
			1,5,7,
			1,3,7,
			0,2,4,
			2,4,6

	};

	std::vector <glm::vec2> texture;


	GLfloat iterY = building.height * 0.005;
	GLfloat iterX = building.width * 0.005;


	texture.push_back(glm::vec2(0.0f, iterY));
	texture.push_back(glm::vec2(iterX, iterY));
	texture.push_back(glm::vec2(0.0f, 0.0f));
	texture.push_back(glm::vec2(iterX, 0.0f));

	texture.push_back(glm::vec2(iterX, iterY));
	texture.push_back(glm::vec2(0.0f, iterY));
	texture.push_back(glm::vec2(iterX, 0.0f));
	texture.push_back(glm::vec2(0.0f, 0.0f));

	GLuint vertexBufferBase;
	GLuint textureBufferBase;

	GLuint indexBufferBase;

	//Object 1 vertex indices
 	glGenBuffers(1, &vertexBufferBase);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferBase);
	glBufferData(GL_ARRAY_BUFFER, building.sommets.size() * sizeof(glm::vec3), building.sommets.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//Object 1 colors
	glGenBuffers(1, &textureBufferBase);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferBase);
	glBufferData(GL_ARRAY_BUFFER, texture.size() * sizeof(glm::vec2), texture.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// Object 1 vertex positions
	glGenBuffers(1, &indexBufferBase);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferBase);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tab), tab, GL_STATIC_DRAW);
}

void ShapeData::MakeFloor(glm::vec3 lowLeft, glm::vec3 highRight, float y, int iter)
{
	GLuint indexBufferCar;
	GLuint colorsBufferCar;
	GLuint vertexBufferCar;

	glm::vec3 vertices[4];
	glm::vec2 floor[4];

	GLfloat width = 0.2;

	//Floor
	vertices[0] = glm::vec3(lowLeft.x - 5, y, lowLeft.z - 5);
	vertices[1] = glm::vec3(highRight.x + 5, y, lowLeft.z -5);
	vertices[2] = glm::vec3(lowLeft.x - 5, y, highRight.z +  5);
	vertices[3] = glm::vec3(highRight.x + 5, y, highRight.z +5);


	floor[0] = glm::vec2(0.0f, 0.0f);
	floor[1] = glm::vec2((GLfloat)iter, 0.0f);
	floor[2] = glm::vec2(0.0f, (GLfloat)iter);
	floor[3] = glm::vec2((GLfloat)iter, (GLfloat)iter);


	


	//Index
	GLuint myIndexShape[] = {
	0,2,1, 3,2,1

	};

	//Object 1 vertex indices
	glGenBuffers(1, &vertexBufferCar);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCar);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	//Texture
	GLuint texVBO;
	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	// Object 1 vertex positions
	glGenBuffers(1, &indexBufferCar);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferCar);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myIndexShape), myIndexShape, GL_STATIC_DRAW);

}

GLfloat ShapeData::RandomColor()
{
	GLfloat c = rand() % 255;
	c = c / 255;
	return c;
}