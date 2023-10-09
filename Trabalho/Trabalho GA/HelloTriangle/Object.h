#pragma once
#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>

//Classe para manipulação dos shaders
#include "Shader.h"

enum direcao { MOVING_TOP_RIGHT, MOVING_TOP_LEFT, MOVING_DOWN_RIGHT, MOVING_DOWN_LEFT };

class Object
{
public:
	Object();
	~Object();
	void initialize(int nAnimations, int nFrames, int randomDirectionNumber);
	inline void setTexID(GLuint texID) { this->texID = texID; }

	inline void setPosition(glm::vec3 position) { this->position = position; }
	inline void setDimensions(glm::vec3 dimensions) { this->dimensions = dimensions; scaleFactor = dimensions; }
	inline void setShader(Shader* shader) { this->shader = shader; }

	void update();
	void draw();

	void moveTopLeft();
	void moveTopRight();
	void moveDownLeft();
	void moveDownRight();

protected:
	GLuint VAO; //identificador do buffer de geometria
	GLuint texID; //identificador do buffer de textura

	//Atributos relacionados às transformações
	glm::vec3 position, dimensions, rotationAxis;
	float angle;
	float vel;
	int direcao;

	Shader* shader; //armazena o endereço do shader

	int nAnimations, nFrames, iAnimation, iFrame;
	float ds, dt;
	glm::vec3 scaleFactor;

};
