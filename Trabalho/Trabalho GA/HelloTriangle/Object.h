#pragma once
#pragma once

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Classe para manipulação dos shaders
#include "Shader.h"

class Object
{
public:
	Object();
	~Object();
	void initialize(int nAnimations, int nFrames);
	inline void setTexID(GLuint texID) { this->texID = texID; }

	inline void setPosition(glm::vec3 position) { this->position = position; }
	inline void setDimensions(glm::vec3 dimensions) { this->dimensions = dimensions; scaleFactor = dimensions; }
	inline void setShader(Shader* shader) { this->shader = shader; }

	void update();
	void draw();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

protected:
	GLuint VAO; //identificador do buffer de geometria
	GLuint texID; //identificador do buffer de textura

	//Atributos relacionados às transformações
	glm::vec3 position, dimensions, rotationAxis;
	float angle;
	float vel;

	Shader* shader; //armazena o endereço do shader

	int nAnimations, nFrames, iAnimation, iFrame;
	float ds, dt;
	glm::vec3 scaleFactor;

};
