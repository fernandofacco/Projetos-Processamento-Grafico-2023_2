#include "Enemy.h"

Enemy::Enemy()
{
	//Inicializar outros atributos
	vel = 5;
}

Enemy::~Enemy()
{
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
}

void Enemy::initialize(int nAnimations, int nFrames, int randomDirectionNumber, int width, int heigth)
{
	this->nAnimations = nAnimations;
	this->nFrames = nFrames;
	this->width = width;
	this->height = height;

	ds = 1.0 / (float)nFrames;
	dt = 1.0 / (float)nAnimations;
	iFrame = 0;
	iAnimation = 0;

	GLfloat vertices[] = {
		//Primeiro Triângulo
		//x   y     z    s    t   
		-0.5, -0.5, 0.0, 0.0, 0.0, //v0
		 0.5,  0.5, 0.0, ds, dt, //v1
		-0.5,  0.5, 0.0, 0.0, dt, //v2

		//Segundo Triângulo
		-0.5, -0.5, 0.0, 0.0, 0.0, //v0
		 0.5, -0.5, 0.0, ds, 0.0, //v3 
		 0.5,  0.5, 0.0, ds, dt, //v1
	};

	GLuint VBO;
	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo coordenada de textura 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// Converta o número aleatório em uma direção
	switch (randomDirectionNumber) {
		case 0:
			direcao = MOVING_TOP_RIGHT;
			break;
		case 1:
			direcao = MOVING_TOP_LEFT;
			break;
		case 2:
			direcao = MOVING_DOWN_RIGHT;
			break;
		case 3:
			direcao = MOVING_DOWN_LEFT;
			break;
		default:
			break;
	}
}

void Enemy::update()
{
	// Movimentacao em diagonal
	switch (direcao) {
		case MOVING_TOP_RIGHT:
			moveTopRight();
			if (position.y >= 900) {
				direcao = MOVING_DOWN_RIGHT;
			}
			if (position.x >= 1440) {
				direcao = MOVING_TOP_LEFT;
			}
			break;
		case MOVING_TOP_LEFT:
			moveTopLeft();
			if (position.y >= 900) {
				direcao = MOVING_DOWN_LEFT;
			}
			if (position.x <= 0) {
				direcao = MOVING_TOP_RIGHT;
			}
			break;
		case MOVING_DOWN_RIGHT:
			moveDownRight();
			if (position.y <= 0) {
				direcao = MOVING_TOP_RIGHT;
			}
			if (position.x >= 1440) {
				direcao = MOVING_DOWN_LEFT;
			}
			break;
		case MOVING_DOWN_LEFT:
			moveDownLeft();
			if (position.y <= 0) {
				direcao = MOVING_TOP_LEFT;
			}
			if (position.x <= 0) {
				direcao = MOVING_DOWN_RIGHT;
			}
			break;
		default:
			break;
	}

	//Conecta com o VAO
	glBindVertexArray(VAO);

	//Altera a matriz a transformação
	glm::mat4 model = glm::mat4(1); //matriz identidade
	//Aplicando as transformações
	model = glm::translate(model, position);
	//rotate..


	model = glm::scale(model, scaleFactor);
	//Enviando a matriz de modelo para o shader
	shader->setMat4("model", glm::value_ptr(model));

	shader->setVec2("offsets", iFrame * ds, iAnimation * dt);


	//Desconecta com o VAO
	glBindVertexArray(0);
}

void Enemy::draw()
{
	//Conecta com o VAO
	glBindVertexArray(VAO);

	//Conecta a textura do sprite
	glBindTexture(GL_TEXTURE_2D, texID);

	//Faz a chamada de desenho
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Desconecta com o VAO
	glBindVertexArray(0);

	//Desconecta a textura
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Enemy::moveTopLeft()
{
	position.x -= vel;
	position.y += vel;
}

void Enemy::moveTopRight()
{
	position.x += vel;
	position.y += vel;
}

void Enemy::moveDownLeft()
{
	position.x -= vel;
	position.y -= vel;
}

void Enemy::moveDownRight()
{
	position.x += vel;
	position.y -= vel;
}