#include "GridMaker.h"






GridMaker::~GridMaker() 
{
}
GridMaker::GridMaker(int scale)
{
	glm::vec3 origin = glm::vec3(-1 * scale, -1.0f, -1 * scale);

	lowLeft = origin;

	srand(time(0));

	int nbRows = rand()%100 + 10; //at least 10
	int nbCols = rand()%100 + 10;  //at least 10 



	getGaussianKernel(nbRows, nbCols, 3,3);


	GLfloat mouvementX = ((2.0f * scale) / (GLfloat)nbRows) ;

	GLfloat mouvementZ = ((2.0f * scale) / (GLfloat)nbCols);


	int nbBlockX = rand() % 10 + 5;

	//Creation des parcelles de terrain
	for (int rows = 0; rows < nbRows; rows++) 
	{
		
		origin.z = -1 * scale;
		for (int cols = 0; cols < nbCols; cols++) 
		{

			parcelles.push_back(Parcelle(origin, mouvementX, mouvementZ, kernel[(rows * nbCols) + cols] * scale));

			origin.z = origin.z + mouvementZ;

			origin.z += 0.1 * (scale/2);

			
		}
		origin.x = origin.x + mouvementX;
		if (rows == nbBlockX) {
			nbBlockX = rand() % 10 + 5;
			origin.x += 0.1 * (scale / 2);
		}
		
		
	}
	highRight = origin;
}

void GridMaker::getGaussianKernel(int rows, int cols, double sigmax, double sigmay)
{
	const auto y_mid = (rows - 1) / 2.0;
	const auto x_mid = (cols - 1) / 2.0;

	const auto x_spread = 1. / (sigmax*sigmax * 2);
	const auto y_spread = 1. / (sigmay*sigmay * 2);

	const auto denominator = 8 * std::atan(1) * sigmax * sigmay;

	std::vector<double> gauss_x, gauss_y;

	gauss_x.reserve(cols);
	for (auto i = 0; i < cols; ++i) {
		auto x = i - x_mid;
		gauss_x.push_back(std::exp(-x * x * x_spread));
	}

	gauss_y.reserve(rows);
	for (auto i = 0; i < rows; ++i) {
		auto y = i - y_mid;
		gauss_y.push_back(std::exp(-y * y * y_spread));
	}

	for (auto j = 0; j < rows; ++j)
		for (auto i = 0; i < cols; ++i) {
			kernel.push_back(gauss_x[i] * gauss_y[j] / denominator);
		}

}



