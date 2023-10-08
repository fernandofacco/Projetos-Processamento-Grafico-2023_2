# Lista 2 #

### 1. Modifique a janela do mundo (window/ortho) para os limites: xmin=-10, xmax=10, ymin=-10, ymax=10 ###
   projection = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);projection = glm::ortho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

### 2. Agora modifique para: xmin=0, xmax=800, ymin=600, ymax=0.  ###
   projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -5.0, 5.0);
   
### 3. Utilizando a câmera 2D do exercício anterior, desenhe algo na tela. O que acontece quando posicionamos os objetos? Por que é útil essa configuração? ###
![image](/Lista2/Prints/3.jpg)

   Os objetos foram posicionados em suas coordenadas especificadas. Em minha execução, os vértices ficaram posicionados exatamente nas coordenadas que passei.
   Essa configuração pode ser útil para mapear coordenadas e desenhar objetos com mais precisão na tela ou janela do aplicativo.

### 4. Modifique o viewport para desenhar a cena apenas no seguinte quadrante da janelada aplicação: ###
![image](/Lista2/Prints/4.jpg)

### 5. Agora, desenhe a mesma cena nos 4 quadrantes. ###
![image](/Lista2/Prints/5.jpg)
