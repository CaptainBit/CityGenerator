#include "Parcelle.h"




Parcelle::~Parcelle(){}
Parcelle::Parcelle(glm::vec3 origin, GLfloat x, GLfloat z, double maxH)
{

	originPoint = origin;
	topRight = glm::vec3(origin.x + x, origin.y, origin.z + z);
	maxH = maxH * 150;
	if (maxH < 80) {
		maxH = 80;
	}
	premTerrain = terrainShape(rand()% 3);
	//Selon le premier type de terrain
	if (premTerrain == terrainShape::HRECTANGLE) 
	{
		glm::vec3 leftCorner = glm::vec3(originPoint.x, originPoint.y, originPoint.z);
		AddBuilding(leftCorner, x, (z/3), maxH);

		/////////////////////////////////////////////////////////////////////////////////////////

		leftCorner.z = leftCorner.z + z / 3;
		AddBuilding(leftCorner, x/2, (z/3)*2, maxH);

		/////////////////////////////////////////////////////////////////////////////////////////
		leftCorner.x = leftCorner.x + x / 2;
		AddBuilding(leftCorner, x / 2, (z / 3) * 2, maxH);


		nbTerrains = 3;

	}
	else if (premTerrain == terrainShape::VRECTANGLE) 
	{
		AddBuilding(originPoint, x/3, z , maxH);
		/////////////////////////////////////////////////////////////////////////////////////////
		glm::vec3 leftCorner = glm::vec3(originPoint.x + x/3, originPoint.y, originPoint.z);

		AddBuilding(leftCorner, (x / 3) ,z, maxH);
		/////////////////////////////////////////////////////////////////////////////////////////
		leftCorner.x = leftCorner.x + x / 3;

		AddBuilding(leftCorner, (x / 3), z, maxH);

		

		nbTerrains = 3;

	}
	else 
	{
		// 2 Big squares
		AddBuilding(originPoint, x / 2, z, maxH);
		/////////////////////////////////////////////////////////////////////////////////////////
		glm::vec3 leftCorner = glm::vec3(originPoint.x + (x / 2), originPoint.y, originPoint.z);
		AddBuilding(leftCorner, x / 2, z, maxH);


		nbTerrains = 2;

	}
}

void Parcelle::AddBuilding(glm::vec3 leftCorner, GLfloat x, GLfloat z, double h)
{
	buildings.push_back(Building(leftCorner,x, h, z));

}



