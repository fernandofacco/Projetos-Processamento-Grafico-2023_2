# Lista 1 #

### 1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam? ###
   GLSL - É uma linguagem parecida com C utilizada para programar os shaders. Os dois tipos de shaders obrigátorios são: vertex shader e fragment shader.
   Vertex Shader - Responsável por processar cada vértice separadamente.
   Fragment Shader - Responsável por processar fragmento cada separadamente.

### 2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL? ###
   São elementos gráficos básicos como pontos, linhas, polígonos e outros. São armazenado através de buffers.
   
### 3. Explique o que é VBO, VAO e EBO, e como se relacionam (se achar mais fácil, pode fazer um gráfico representando a relação entre eles). ###
   VBO - É um buffer que é utilizado para armazenar os dados (coordenadas) dos vértices na memória e enviá-los à GPU.
   VAO - É um buffer que é utilizado para fazer a ligação dos atributos de um vértice (posição e cores).
   EBO - é um buffer que é utilizado para para armazenar índices que são utilizados para decidir a ordem dos vértices a serem desenhados.

### 4. Analise o código fonte do projeto Hello Triangle. Localize e relacione os conceitos de shaders, VBOs e VAO apresentados até então. Não precisa entregar nada neste exercício. ###

### 5. Faça o desenho de 2 triângulos na tela. Desenhe eles: ###
### a. Apenas com o polígono preenchido ###
![image](/Lista1/Prints/5a.jpg)

### b. Apenas com contorno ###
![image](/Lista1/Prints/5b.jpg)

### c. Apenas como pontos ###
![image](/Lista1/Prints/5c.jpg)

### d. Com as 3 formas de desenho juntas ###
![image](/Lista1/Prints/5d.jpg)

### 6. Faça o desenho de um círculo na tela, utilizando a equação paramétrica do círculo para gerar os vértices. Depois disso: ###
![image](/Lista1/Prints/6.jpg)

### a) Desenhe um octágono ###
![image](/Lista1/Prints/6a.jpg)

### b) Desenhe um pentágono ###
![image](/Lista1/Prints/6b.jpg)

### c) Desenhe um pac-man! ###
![image](/Lista1/Prints/6c.jpg)

### d) Desenhe uma fatia de pizza ###
![image](/Lista1/Prints/6d.jpg)

### e) DESAFIO: desenhe uma “estrela” ###
![image](/Lista1/Prints/6e.jpg)

### 7. Desenhe uma espiral: ###
![image](/Lista1/Prints/7.jpg)

### 8. Considerando o seguinte triângulo abaixo, formado pelos vértices P1, P2 e P3, respectivamente com as cores vermelho, verde e azul. ###
![image](/Lista1/Prints/8.jpg)
