![5a](https://github.com/fernandofacco/Projetos-Processamento-Grafico-2023_2/assets/88943228/c941c735-4043-4e20-8ae4-90273f1a2eaf)# Lista 1

1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?
   GLSL - É uma linguagem parecida com C utilizada para programar os shaders. Os dois tipos de shaders obrigátorios são: vertex shader e fragment shader.
   Vertex Shader - Responsável por processar cada vértice separadamente.
   Fragment Shader - Responsável por processar fragmento cada separadamente.

2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?
   São elementos gráficos básicos como pontos, linhas, polígonos e outros. São armazenado através de buffers.
   
4. Explique o que é VBO, VAO e EBO, e como se relacionam (se achar mais fácil, pode fazer um gráfico representando a relação entre eles).
   VBO - É um buffer que é utilizado para armazenar os dados (coordenadas) dos vértices na memória e enviá-los à GPU.
   VAO - É um buffer que é utilizado para fazer a ligação dos atributos de um vértice (posição e cores).
   EBO - é um buffer que é utilizado para para armazenar índices que são utilizados para decidir a ordem dos vértices a serem desenhados.

5. Analise o código fonte do projeto Hello Triangle. Localize e relacione os conceitos de shaders, VBOs e VAO apresentados até então. Não precisa entregar nada neste exercício.

6. Faça o desenho de 2 triângulos na tela. Desenhe eles:
a. Apenas com o polígono preenchido
![5a](https://github.com/fernandofacco/Projetos-Processamento-Grafico-2023_2/assets/88943228/8bd8e34a-54a5-4c77-add3-370084a2a7a8)


b. Apenas com contorno

c. Apenas como pontos

d. Com as 3 formas de desenho juntas

6. Faça o desenho de um círculo na tela, utilizando a equação paramétrica do círculo para gerar os vértices. Depois disso:

a) Desenhe um octágono

b) Desenhe um pentágono

c) Desenhe um pac-man!

d) Desenhe uma fatia de pizza

e) DESAFIO: desenhe uma “estrela”

7. Desenhe uma espiral:

8. Considerando o seguinte triângulo abaixo, formado pelos vértices P1, P2 e P3, respectivamente com as cores vermelho, verde e azul.
