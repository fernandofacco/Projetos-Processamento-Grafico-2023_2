#include "Object.h"

Object::Object()
{
	//Inicializar outros atributos
	vel = 5;
}

Object::~Object()
{
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
}

void Object::initialize(int nAnimations, int nFrames, int randomDirectionNumber)
{
	this->nAnimations = nAnimations;
	this->nFrames = nFrames;
	ds = 1.0 / (float)nFrames;
	dt = 1.0 / (float)nAnimations;
	iFrame = 0;
	iAnimation = 0;

	GLfloat vertices[] = {
		//Primeiro Tri�ngulo
		//x   y     z    s    t   
		-0.5, -0.5, 0.0, 0.0, 0.0, //v0
		 0.5,  0.5, 0.0, ds, dt, //v1
		-0.5,  0.5, 0.0, 0.0, dt, //v2

		//Segundo Tri�ngulo
		-0.5, -0.5, 0.0, 0.0, 0.0, //v0
		 0.5, -0.5, 0.0, ds, 0.0, //v3 
		 0.5,  0.5, 0.0, ds, dt, //v1
	};

	GLuint VBO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo coordenada de textura 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// Converta o n�mero aleat�rio em uma dire��o
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
			std::cerr << "Erro: Valor aleat�rio fora do intervalo esperado." << std::endl;
	}
}

void Object::update()
{
	switch (direcao) {
		case MOVING_TOP_RIGHT:
			moveTopRight();
			if (position.y >= 600) {
				direcao = MOVING_DOWN_RIGHT;
			}
			if (position.x >= 800) {
				direcao = MOVING_TOP_LEFT;
			}
			break;
		case MOVING_TOP_LEFT:
			moveTopLeft();
			if (position.y >= 600) {
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
			if (position.x >= 800) {
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
	/*if (direcao == MOVING_TOP_RIGHT)
	{
		moveDown();

		// Verifique se atingiu o limite superior da tela e, se sim, mude a dire��o.
		if (position.y <= 0)
		{
			indoParaBaixo = false;
		}
	}
	else if (indoParaBaixo == false)
	{
		moveUp();

		// Verifique se atingiu o limite inferior da tela e, se sim, mude a dire��o.
		if (position.y >= 600)
		{
			indoParaBaixo = true;
		}
	}*/
	//Conecta com o VAO
	glBindVertexArray(VAO);

	//Altera a matriz a transforma��o
	glm::mat4 model = glm::mat4(1); //matriz identidade
	//Aplicando as transforma��es
	model = glm::translate(model, position);
	//rotate..


	model = glm::scale(model, scaleFactor);
	//Enviando a matriz de modelo para o shader
	shader->setMat4("model", glm::value_ptr(model));

	shader->setVec2("offsets", iFrame * ds, iAnimation * dt);


	//Desconecta com o VAO
	glBindVertexArray(0);
}

void Object::draw()
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

void Object::moveTopLeft()
{
	position.x -= vel;
	position.y += vel;
}

void Object::moveTopRight()
{
	position.x += vel;
	position.y += vel;
}

void Object::moveDownLeft()
{
	position.x -= vel;
	position.y -= vel;
}

void Object::moveDownRight()
{
	position.x += vel;
	position.y -= vel;
}