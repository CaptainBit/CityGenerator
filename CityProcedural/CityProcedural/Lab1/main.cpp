
#include <iostream>

/******APIs*****/
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "Dependencies\soil\src\SOIL.h"

/*****Classes personnalisées*******/
#include "ShaderLoader\Shader_Loader.h"
#include "HouseMaker\House_Maker.h"
#include "TextureLoader\Texture_Loader.h"

/**Classe faite par moi :) **/
#include "City\GridMaker.h"
#include "City\Parcelle.h"
#include "City\ShapeData.h"



/**********namespaces**************/
using namespace Core;
using namespace House;
using namespace texCore;


/****Handlers globaux*****/
GLuint textureProgram;
GLuint skyboxProgram;

std::vector <GLuint> tabGras;
std::vector <GLuint> tabVao;
std::vector <GLuint> tabTex;

GLuint vaoBase;
GLuint vaoToit;
GLuint vaoSol;
GLuint vaoNuage[2];
GLuint vaoSkybox;

GLuint gProjection;
GLuint gVue;
GLuint gModele;

GLuint texMaison[3];
GLuint texSol;
GLuint texToit;
GLuint texNuage;
GLuint texGrass;
GLuint texSkybox;




/******variables globales*******/


glm::vec3 cameraPos = glm::vec3(0.0f, 4.0f, 7.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float multipleCouleur[4] = { 1.0,1.0,1.0,1.0 };
bool firstMouse = true;
bool firstKey = false;
GLfloat yaw = -90.0f;	
GLfloat pitch = 0.0f;
GLfloat lastX = 0;
GLfloat lastY = 0;
bool boutons[4] = { false,false,false,false };
bool warpsouris=false;

void getUniforms(GLuint *program)
{
	glUseProgram(*program);
	gProjection = glGetUniformLocation(*program, "gProjection");
	assert(gProjection != 0xFFFFFFFF);

	gVue = glGetUniformLocation(*program, "gVue");
	assert(gVue != 0xFFFFFFFF);

	
}



void deplacement()
{
	GLfloat cameraSpeed = 1.3f;
	glm::vec3 camDevant;
	camDevant.x = cameraFront.x;
	camDevant.z = cameraFront.z;

	if (boutons[0] == true) {
		cameraPos -= glm::normalize(glm::cross(camDevant, cameraUp)) * cameraSpeed;
	}
	if (boutons[1] == true) {
		cameraPos += cameraSpeed * camDevant;
	}
	if (boutons[2] == true) {
		cameraPos -= cameraSpeed * camDevant;
	}
	if (boutons[3] == true) {
		cameraPos += glm::normalize(glm::cross(camDevant, cameraUp)) * cameraSpeed;
	}

	
}

void renduMaison()
{
	float randY = 1.0;
	glm::mat4 modele=glm::mat4(1.0);

	

	for (int i = 0; i < tabVao.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, texMaison[tabTex[i]]);
		glBindVertexArray(tabVao[i]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

	glBindTexture(GL_TEXTURE_2D,texGrass);
	for (int i = 0; i < tabGras.size(); i++) {
		glBindVertexArray(tabGras[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

}
void drawSkybox()
{
	// skybox cube
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxProgram, "Skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texSkybox);
	glBindVertexArray(vaoSkybox);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}

//Fonction de rappel du rendu graphique
void renduScene()
{
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 modele;

	deplacement();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	
	projection = glm::perspective(glm::radians(60.0f), glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)*1.0f, 0.1f, 5000.0f);
	
	getUniforms(&skyboxProgram);
	view = glm::mat4(glm::mat3(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)));
	glUniformMatrix4fv(gProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(gVue, 1, GL_FALSE, &view[0][0]);
	drawSkybox();
	
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	gModele = glGetUniformLocation(textureProgram, "gModele");
	assert(gModele != 0xFFFFFFFF);

	getUniforms(&textureProgram);
	glUniformMatrix4fv(gProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(gVue, 1, GL_FALSE, &view[0][0]);
	glUniform4fv(glGetUniformLocation(textureProgram, "color"), 1, multipleCouleur);

	glActiveTexture(GL_TEXTURE0);

	renduMaison();

	modele = glm::mat4(1.0);
	glUniformMatrix4fv(gModele, 1, GL_FALSE, &modele[0][0]);

	glBindVertexArray(vaoSol);
	glBindTexture(GL_TEXTURE_2D, texSol);
	glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(vaoNuage[i]);
		glBindTexture(GL_TEXTURE_2D, texNuage);
		glUniform1i(glGetUniformLocation(textureProgram, "ourTexture1"), 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		
	}

	

	glutSwapBuffers();


	
}

void clavier(unsigned char bouton, int x, int y)
{
	switch (bouton)
	{
	case 'a':
		boutons[0] = true;
		
		break;
	case 'w':
		boutons[1] = true;
		
		break;
	case 's':
		boutons[2] = true;
		
		break;
	case 'd':
		boutons[3] = true;
		
		break;
	case 27:
		glutLeaveMainLoop();
		break;

	}
	
}



void souris(int x, int y)
{

	if (warpsouris)
	{
		warpsouris = false;
		lastX = x;
		lastY = y;
	}
	else
	{
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		GLfloat xoffset = x - lastX;
		GLfloat yoffset = lastY - y;
		lastX = x;
		lastY = y;

		GLfloat sensitivity = 0.3;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);

		
		warpsouris = true;
		
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		
	}

	

}

void dessineMaison()
{	
	House_Maker* maMaison = new House_Maker();

	GridMaker* grid = new GridMaker(800);

	ShapeData* city = new ShapeData();

	tabVao.clear();
	tabTex.clear();
	tabGras.clear();

	for (int i = 0; i < grid->parcelles.size(); i++) 
	{
		for (int j = 0; j < grid->parcelles[i].nbTerrains; j++)
		{
		
			tabTex.push_back(rand() % 3);
			tabVao.push_back(0);

			glGenVertexArrays(1, &tabVao[tabVao.size()-1]);
			glBindVertexArray(tabVao[tabVao.size() - 1]);
			city->MakeBase(grid->parcelles[i].buildings[j]);
			glBindVertexArray(0);

			tabGras.push_back(0);
			glGenVertexArrays(1, &tabGras[tabVao.size() - 1]);
			glBindVertexArray(tabGras[tabVao.size() - 1]);
			city->MakeFloor(grid->parcelles[i].buildings[j].lowLeft, grid->parcelles[i].buildings[j].highRight, -1.05, 1);
			glBindVertexArray(0);


		}
	}

	glBindVertexArray(vaoSol);
	city->MakeFloor(grid->lowLeft, grid->highRight, -1.1, 400);
	glBindVertexArray(0);



	glBindVertexArray(vaoNuage[0]);
	maMaison->creeSurface(600.0,700.0,700.0, 1.0, true, false);
	glBindVertexArray(0);

	glBindVertexArray(vaoNuage[1]);
	maMaison->creeSurface(600.0,500.0, 700.0, 2.0, true, false);
	glBindVertexArray(0);



	glBindVertexArray(vaoSkybox);
	maMaison->creeBase(1.0, 1.0, 1.0, glm::vec3(1.0, 0.0, 0.0));
	glBindVertexArray(0);

	delete city;
	delete maMaison;
	delete grid;
}

void releaseClavier(unsigned char bouton, int x, int y)
{

	switch (bouton)
	{
	case 'a':
		boutons[0] = false;
		break;
	case 'w':
		boutons[1] = false;
		break;
	case 's':
		boutons[2] = false;
		break;
	case 'd':
		boutons[3] = false;
		break;
	case 'r':
		dessineMaison();
		break;
	case 'z':
		cameraPos.y += 10;
		break;

	case 'x':
		if(cameraPos.y > 4)
			cameraPos.y -= 10;
		break;
	}
}
/*****************************************/
//Fonction d'initialisation des textures
void initTextures()
{
	Texture_Loader textureLoader;
	texMaison[0] = textureLoader.CreateTexture2D("textures/tower.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texMaison[1] = textureLoader.CreateTexture2D("textures/tower1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texMaison[2] = textureLoader.CreateTexture2D("textures/tower2.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
	texSol = textureLoader.CreateTexture2D("textures/route.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);
	texToit = textureLoader.CreateTexture2D("textures/toit2.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);
	
	texNuage = textureLoader.CreateTexture2D("textures/cloud.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA);
	
	texGrass = textureLoader.CreateTexture2D("textures/grass.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);

	std::vector<char*> faces;
	faces.push_back("textures/right.jpg");
	faces.push_back("textures/left.jpg");
	faces.push_back("textures/top.jpg");
	faces.push_back("textures/bottom.jpg");
	faces.push_back("textures/back.jpg");
	faces.push_back("textures/front.jpg");
	texSkybox = textureLoader.CreateSkyboxTexture(faces);
}

/*****************************************/
//Fonction d'initialisation des shaders
void initShaders()
{
	Core::Shader_Loader shaderLoader;
	textureProgram = shaderLoader.CreateProgram("vertexShader.glsl", "fragmentShader.glsl");
	skyboxProgram = shaderLoader.CreateProgram("vertSkybox.glsl", "fragSkybox.glsl");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glGenVertexArrays(1, &vaoBase);
	glGenVertexArrays(1, &vaoToit);
	glGenVertexArrays(1, &vaoSol);
	glGenVertexArrays(2, vaoNuage);
	glGenVertexArrays(1, &vaoSkybox);

}
void passeTemps(int temps)
{
	multipleCouleur[temps] -= 0.5;
	temps++;

	if(temps == 4)
	{
		multipleCouleur[0] = 1.0;
		multipleCouleur[1] = 1.0;
		multipleCouleur[2] = 1.0;
		multipleCouleur[3] = 1.0;
		temps = 0;
	}
	
	glutTimerFunc(5000, passeTemps, temps);
}

/******************************************/

void fermeture()
{
	glutLeaveMainLoop();
}

//Fonction principale d'initialisation et d'exécution
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutCreateWindow("Maison 3D");
	glutFullScreen();

	/*******************/
	glewInit();

	initShaders();
		
	/******************/

	glutDisplayFunc(renduScene);
	glutCloseFunc(fermeture);
	glutKeyboardFunc(clavier);
	glutPassiveMotionFunc(souris);
	glutKeyboardUpFunc(releaseClavier);
	glutIdleFunc(renduScene);
	//glutTimerFunc(5000,passeTemps,0);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glClearColor(0.0f, 0.4f, 0.5f, 0.0f);

	glutSetCursor(GLUT_CURSOR_NONE);

	/***Initialisation de la maison****/
	initTextures();
	dessineMaison();

	/**********************************/
	
	glutMainLoop();

	/***************/
	glDeleteVertexArrays(1, &vaoBase);
	glDeleteVertexArrays(1, &vaoToit);
	glDeleteVertexArrays(1, &vaoSol);
	glDeleteVertexArrays(2, vaoNuage);
	glDeleteProgram(skyboxProgram);
	glDeleteProgram(textureProgram);
	/**************/

	return 0;
}

