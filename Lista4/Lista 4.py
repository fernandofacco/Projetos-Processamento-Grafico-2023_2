import numpy as np
import cv2 as cv

img = cv.imread('baboon.png') # Original
imgRed = img.copy() # Canal Red
imgGreen = img.copy() # Canal Green
imgBlue = img.copy() # Canal Blue
imgGray = img.copy() # Grayscale
imgInversao = img.copy() # Inversão
imgBinarizacao = cv.cvtColor(img,cv.COLOR_BGR2GRAY) # Binarização
imgVignette = img.copy() # Efeito Vignette
corModificadoraRed = [255, 0, 0]
corModificadoraGreen = [0, 255, 0]
corModificadoraBlue = [0, 0, 255]

valorLimite = 130

for i in range(img.shape[0]): #percorre linhas
    for j in range(img.shape[1]): #percorre colunas
        # a. Red
        B = img.item(i,j,0) | corModificadoraRed[2]
        G = img.item(i,j,1) | corModificadoraRed[1]
        R = img.item(i,j,2) | corModificadoraRed[0]
        imgRed.itemset((i,j,0),B) # canal B
        imgRed.itemset((i,j,1),G) # canal G
        imgRed.itemset((i,j,2),R) # canal R

        # a. Green                
        B = img.item(i,j,0) | corModificadoraGreen[2]
        G = img.item(i,j,1) | corModificadoraGreen[1]
        R = img.item(i,j,2) | corModificadoraGreen[0]
        imgGreen.itemset((i,j,0),B) # canal B
        imgGreen.itemset((i,j,1),G) # canal G
        imgGreen.itemset((i,j,2),R) # canal R

        # a. Blue
        B = img.item(i,j,0) | corModificadoraBlue[2]
        G = img.item(i,j,1) | corModificadoraBlue[1]
        R = img.item(i,j,2) | corModificadoraBlue[0]
        imgBlue.itemset((i,j,0),B) # canal B
        imgBlue.itemset((i,j,1),G) # canal G
        imgBlue.itemset((i,j,2),R) # canal R

        # b. Grayscale - Média ponderada
        mediaPond = img.item(i,j,0) * 0.07 + img.item(i,j,1) * 0.71 + img.item(i,j,2) * 0.21
        imgGray.itemset((i,j,0),mediaPond) # canal B
        imgGray.itemset((i,j,1),mediaPond) # canal G
        imgGray.itemset((i,j,2),mediaPond) # canal R

        # d. Inversão
        imgInversao.itemset((i,j,0),imgInversao.item(i,j,0)^255) # canal B
        imgInversao.itemset((i,j,1),imgInversao.item(i,j,1)^255) # canal G
        imgInversao.itemset((i,j,2),imgInversao.item(i,j,2)^255) # canal R

        # e. Binarização
        if imgBinarizacao.item(i,j) < valorLimite:
            imgBinarizacao.itemset((i,j),0)
        else:
            imgBinarizacao.itemset((i,j),255)
		
 # f. Meu filtro - Sharp
sharpKernel = np.array([[-1, -1, -1], [-1, 9.5, -1], [-1, -1, -1]])
imgSharp = cv.filter2D(img, -1, sharpKernel)

# g. Vignette
rows, cols = img.shape[:2]
   
Xkernel = cv.getGaussianKernel(cols,200)
Ykernel = cv.getGaussianKernel(rows,200)
   
resultantKernel = Ykernel * Xkernel.T

mask = 255 * resultantKernel / np.linalg.norm(resultantKernel)
   
for i in range(3):
    imgVignette[:,:,i] = imgVignette[:,:,i] * mask
       
cv.imshow("Original",img)
cv.imshow("a. Red",imgRed)
cv.imshow("a. Green",imgGreen)
cv.imshow("a. Blue",imgBlue)
cv.imshow("b. Grayscale - Media Ponderada",imgGray)
cv.imshow("d. Inversao",imgInversao)
cv.imshow("e. Binarizacao",imgBinarizacao)
cv.imshow("f. Meu filtro - Sharp",imgSharp)
cv.imshow("g. Vignette",imgVignette)

cv.waitKey(0)
cv.destroyAllWindows()