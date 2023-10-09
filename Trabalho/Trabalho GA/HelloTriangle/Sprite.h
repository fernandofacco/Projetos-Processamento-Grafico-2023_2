#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Classe para manipula��o dos shaders
#include "Shader.h"

enum states { MOVING_RIGHT, MOVING_LEFT, MOVING_UP, MOVING_DOWN, IDLE };

class Sprite
{
public:
	Sprite();
	~Sprite();
	void initialize(int nAnimations, int nFrames);
	inline void setTexID(GLuint texID) { this->texID = texID; }

	inline void setPosition(glm::vec3 position) { this->position = position; }
	inline glm::vec3 getPosition() { return position; }
	inline void setDimensions(glm::vec3 dimensions) { this->dimensions = dimensions; scaleFactor = dimensions; }
	inline glm::vec3 getDimensions() { return dimensions; }
	inline void setShader(Shader* shader) { this->shader = shader; }
	inline void setState(int state) { this->state = state; }

	void update();
	void draw();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

protected:
	GLuint VAO; //identificador do buffer de geometria
	GLuint texID; //identificador do buffer de textura

	//Atributos relacionados �s transforma��es
	glm::vec3 position, dimensions, rotationAxis;
	float angle;
	float vel;

	Shader* shader; //armazena o endere�o do shader

	int nAnimations, nFrames, iAnimation, iFrame;
	float ds, dt;
	int state;
	glm::vec3 scaleFactor;

};
