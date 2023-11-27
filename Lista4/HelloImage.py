import numpy as np
import cv2 as cv

img = cv.imread('baboon.png') #original
img2 = img.copy() #copia para img modificada
img3 = img.copy()
img10 = img.copy()

img4 = img.copy()
corModificadora = [255, 0, 0]

img5 = cv.imread('bolinhas.png') #original
img6 = img5.copy()

img7 = cv.cvtColor(img,cv.COLOR_BGR2GRAY)
img8 = img7.copy()
k = 150

img9 = img.copy()


print(img.shape) #exibe informações de dimensões e nro de canais

print(img7.shape)

for i in range(img.shape[0]): #percorre linhas
	for j in range(img.shape[1]): #percorre colunas
		media = img.item(i,j,0) * 0.333 + img.item(i,j,1) * 0.333 + img.item(i,j,2) * 0.3333
		img2.itemset((i,j,0),media) # canal B
		img2.itemset((i,j,1),media) # canal G
		img2.itemset((i,j,2),media) # canal R

		mediaPond = img.item(i,j,0) * 0.07 + img.item(i,j,1) * 0.71 + img.item(i,j,2) * 0.21
		img3.itemset((i,j,0),mediaPond) # canal B
		img3.itemset((i,j,1),mediaPond) # canal G
		img3.itemset((i,j,2),mediaPond) # canal R

		B = img10.item(i,j,0)
		img10.itemset((i,j,0),B) # canal B
		img10.itemset((i,j,1),B) # canal G
		img10.itemset((i,j,2),B) # canal R

		B = img.item(i,j,0) | corModificadora[0]
		G = img.item(i,j,1) | corModificadora[1]
		R = img.item(i,j,2) | corModificadora[2]
		img4.itemset((i,j,0),B) # canal B
		img4.itemset((i,j,1),G) # canal G
		img4.itemset((i,j,2),R) # canal R

		img6.itemset((i,j,0),img6.item(i,j,0)^255) # canal B
		img6.itemset((i,j,1),img6.item(i,j,1)^255) # canal G
		img6.itemset((i,j,2),img6.item(i,j,2)^255) # canal R

		if img7.item(i,j) < k:
			img8.itemset((i,j),0)
		else:
			img8.itemset((i,j),255)
		
		#"color ramp"
		if img7.item(i,j) < 100:
			img9.itemset((i,j,0),255)
			img9.itemset((i,j,1),255)
			img9.itemset((i,j,2),0)
		elif img7.item(i,j) < 150:
			img9.itemset((i,j,0),255)
			img9.itemset((i,j,1),0)
			img9.itemset((i,j,2),255)
		else:
			img9.itemset((i,j,0),0)
			img9.itemset((i,j,1),255)
			img9.itemset((i,j,2),255)

cv.imshow("Original",img)
# cv.imshow("Grayscale - Média Aritmética",img2)
# cv.imshow("Grayscale - Média Ponderada",img3)
# cv.imshow("Grayscale - Apenas um canal",img10)
cv.imshow("Imagem colorizada",img4)
cv.imshow("Imagem invertida",img6)
cv.imshow("Imagem Grayscale - OpenCV",img7)
cv.imshow("Imagem Binarizada",img8)
cv.imshow("Imagem Color Ramp",img9)

cv.waitKey(0)
cv.destroyAllWindows()