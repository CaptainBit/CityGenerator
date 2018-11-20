#include "Building.h"



Building::Building(glm::vec3 leftCorner, GLfloat x, GLfloat y, GLfloat z)
{

	height = y;
	width = x;


	GLfloat pTerrain = ((GLfloat)(rand() % 30 + 30)/100);

	lowLeft = glm::vec3(leftCorner.x + 0.2, leftCorner.y, leftCorner.z + 0.2);

	highRight = glm::vec3(leftCorner.x + x * pTerrain , leftCorner.y, leftCorner.z + z * pTerrain);


	sommets.push_back(glm::vec3(leftCorner.x, leftCorner.y + (y * pTerrain), leftCorner.z));
	sommets.push_back(glm::vec3(leftCorner.x + (x * pTerrain), leftCorner.y + (y * pTerrain), leftCorner.z));
	sommets.push_back(glm::vec3(leftCorner.x, leftCorner.y, leftCorner.z));
	sommets.push_back(glm::vec3(leftCorner.x + (x*pTerrain), leftCorner.y, leftCorner.z));
	sommets.push_back(glm::vec3(leftCorner.x, leftCorner.y + (y *pTerrain), leftCorner.z + (z * pTerrain)));
	sommets.push_back(glm::vec3(leftCorner.x + (x * pTerrain), leftCorner.y + (y * pTerrain), leftCorner.z + (z * pTerrain)));
	sommets.push_back(glm::vec3(leftCorner.x, leftCorner.y, leftCorner.z + (z * pTerrain)));
	sommets.push_back(glm::vec3(leftCorner.x + (x * pTerrain), leftCorner.y, leftCorner.z + z * pTerrain));

}

