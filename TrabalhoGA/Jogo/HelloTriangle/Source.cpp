#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;


// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//STB_IMAGE
#include <stb_image.h>

//Classe para manipula��o dos shaders
#include "Shader.h"

//Classe Sprite 
#include "Sprite.h"

#include "Enemy.h"

//Classe Timer
#include "Timer.h"

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

bool checkCollision(Sprite& object1, Enemy& object2);

// Prot�tipos das fun��es
int setupGeometry();
int setupTexture(string filePath, int &width, int &height);
int setupSprite();

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 1440, HEIGHT = 900;

Sprite personagem; 
// Object meuArrayFixo[100];

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Vetor contendo todos os inimigos
	std::vector<Enemy> vetorInimigos;
	vetorInimigos.reserve(100);

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo! -- Fernando", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");

	shader.Use();

	//Fazendo a leitura da textura do personagem
	int sprWidth, sprHeight;
	//int texID = setupTexture("../../Textures/characters/PNG/Knight/walk.png", sprWidth, sprHeight);
	int texID = setupTexture("../../Textures/Run.png", sprWidth, sprHeight);

	int sprWidth2, sprHeight2;
	//int texID2 = setupTexture("../../Textures/characters/PNG/Mage/mage.png", sprWidth2, sprHeight2);
	int texID2 = setupTexture("../../Textures/walk1.png", sprWidth2, sprHeight2);

	int sprWidth3, sprHeight3;
	int texID3 = setupTexture("../../Textures/backgrounds/PNG/Postapocalypce1/Bright/postapocalypse1.png", sprWidth3, sprHeight3);

	// Criando a inst�ncia de nosso objeto sprite do Personagem
	personagem.initialize(1, 7);
	personagem.setPosition(glm::vec3(400.0, 300.0, 0.0));
	personagem.setDimensions(glm::vec3(sprWidth/7, sprHeight, 1.0));
	personagem.setShader(&shader);
	personagem.setTexID(texID);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	for (int i = 0; i < 10; i++) {
		int canto = std::rand() % 4; // 0: cima, 1: direita, 2: baixo, 3: esquerda
		int randomXAxis = 0;
		int randomYAxis = 0;

		switch (canto) {
		case 0: // Cima
			randomXAxis = 10 + (std::rand() % (width - 100)) + 50;
			randomYAxis = height - 10;
			break;
		case 1: // Direita
			randomXAxis = width - 10;
			randomYAxis = 10 + (std::rand() % (height - 100)) + 50;
			break;
		case 2: // Baixo
			randomXAxis = 10 + (std::rand() % (width - 100)) + 50;
			randomYAxis = 10;
			break;
		case 3: // Esquerda
			randomXAxis = 10;
			randomYAxis = 10 + (std::rand() % (height - 100)) + 50;
			break;
		}

		Enemy enemy;
		enemy.initialize(1, 11);
		enemy.setPosition(glm::vec3(randomXAxis, randomYAxis, 1.0));
		enemy.setDimensions(glm::vec3(sprWidth2/11, sprHeight2, 1.0));
		enemy.setShader(&shader);
		enemy.setTexID(texID2);
		vetorInimigos.push_back(enemy);
	}

	//Criando a inst�ncia de nosso objeto sprite do fundo (background)
	Sprite background;
	background.initialize(1,1);
	background.setPosition(glm::vec3(400.0, 300.0, 0.0));
	background.setDimensions(glm::vec3(sprWidth3+200, sprHeight3+200, 1.0));
	background.setShader(&shader);
	background.setTexID(texID3);	


	//Cria a matriz de proje��o paralela ortog�fica
	glm::mat4 projection = glm::mat4(1); //matriz identidade
	projection = glm::ortho(0.0, 1440.0, 0.0, 900.0, -1.0, 1.0);
	
	shader.setMat4("projection", glm::value_ptr(projection));
	shader.setInt("texbuffer", 0);

	glActiveTexture(GL_TEXTURE0);

	//Habilitando a transpar�ncia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Habilitando o teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	Timer timer;

	time_t startTime = time(nullptr);
	int contador = 0;

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// C�lculo de tempo desde o �ltimo inimigo criado
		time_t currentTime = time(nullptr);
		double elapsedTime = difftime(currentTime, startTime);

		timer.start();
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		// Recuperando o tamanho da janela da aplica��o
		glfwGetFramebufferSize(window, &width, &height);
		// Dimensiona a viewport
		glViewport(0, 0, width, height);

		//-------------------------------------------------------------
		background.update();
		background.draw();
		//-------------------------------------------------------------
		personagem.update();
		personagem.draw();
		//-------------------------------------------------------------

		// Criar inimigos a cada X segundos
		if (elapsedTime >= 2.0) {
			contador++; 
			startTime = currentTime; 
		}

		for (int i = 0; i < vetorInimigos.size() && i < contador; i++) {
			vetorInimigos[i].update();
			vetorInimigos[i].draw();

			if (checkCollision(personagem, vetorInimigos[i])) {
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
		}
		//--------------------------------------------------------------

		timer.finish();
		double waitingTime = timer.calcWaitingTime(24, timer.getElapsedTimeMs());
		if (waitingTime)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((int)waitingTime));
		}

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if ( key == GLFW_KEY_A || key == GLFW_KEY_LEFT )
	{
		personagem.setState(MOVING_LEFT);
		personagem.moveLeft();
	}
	if ( key == GLFW_KEY_D || key == GLFW_KEY_RIGHT )
	{
		personagem.setState(MOVING_RIGHT);	
		personagem.moveRight();
	}
	if (key == GLFW_KEY_W|| key == GLFW_KEY_UP)
	{
		personagem.setState(MOVING_UP);
		personagem.moveUp();
	}
	if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
	{
		personagem.setState(MOVING_DOWN);
		personagem.moveDown();
	}
	if (action == GLFW_RELEASE) //soltou a tecla
	{
		personagem.setState(IDLE);
	}
}

// Esta fun��o est� bastante harcoded - objetivo � criar os buffers que armazenam a 
// geometria de um tri�ngulo
// Apenas atributo coordenada nos v�rtices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A fun��o retorna o identificador do VAO
int setupGeometry()
{
	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados
	GLfloat vertices[] = {
		//x   y     z    s    t   
		-0.5, -0.5, 0.0, 0.0, 0.0,//v0
		 0.5, -0.5, 0.0, 1.0, 0.0,//v1
 		 0.0,  0.5, 0.0, 0.5, 1.0 //v2 
	};

	GLuint VBO, VAO;
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
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posi��o
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo coordenada de textura 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}

int setupTexture(string filePath, int &width, int &height)
{
	GLuint texID;
	// Gera��o do identificador do buffer
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configurando par�metro de wrapping da textura em s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//Configurando o par�metro de filtering de magnifica��o e minifica��o da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	
	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels,0);
	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

	}
	else
	{
		cout << "Erro ao ler a textura!" << endl;
		return -1;
	}
	
	return texID;
}

int setupSprite()
{
	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados
	GLfloat vertices[] = {
		//Primeiro Tri�ngulo
		//x   y     z    s    t   
		-0.5, -0.5, 0.0, 0.0, 0.0, //v0
		 0.5,  0.5, 0.0, 1.0, 1.0, //v1
		-0.5,  0.5, 0.0, 0.0, 1.0, //v2

		//Segundo Tri�ngulo
		-0.5, -0.5, 0.0, 0.0, 0.0, //v0
		 0.5, -0.5, 0.0, 1.0, 0.0, //v3 
		 0.5,  0.5, 0.0, 1.0, 1.0, //v1
	};

	GLuint VBO, VAO;
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
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posi��o
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo coordenada de textura 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}


bool checkCollision(Sprite& object1, Enemy& object2) {
	// Obt�m as posi��es e dimens�es dos objetos
	glm::vec3 pos1 = object1.getPosition();
	glm::vec3 pos2 = object2.getPosition();
	glm::vec3 size1 = object1.getDimensions();
	glm::vec3 size2 = object2.getDimensions();

	// Verifica se ocorre colis�o com base nas coordenadas das bounding boxes
	if (pos1.x + (size1.x - 100) > pos2.x && pos1.x < pos2.x + (size2.x - 100) &&
		pos1.y + (size1.y - 100) > pos2.y && pos1.y < pos2.y + (size2.y - 100)) {
		// Colis�o detectada
		return true;
	}

	// N�o h� colis�o
	return false;
}