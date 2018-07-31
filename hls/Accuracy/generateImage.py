import cv2
import math
import numpy as np

sample = cv2.imread("fov.jpg")
img = cv2.imread("cube.jpg")
fov = np.zeros((1024,1024,3), np.uint8)
cv2.waitKey(0)
i =0
j = -1
for count in range(0,11):
	inf = open(str(count)+".txt","r")
	for line in inf:

		m,n = line.split(",")
		a = i%1024
		if a == 0:
			j += 1
		fov[j,a] = img[int(n)-1, int(m)-1]
		i += 1
	cv2.imwrite(str(count)+".jpg",fov)
	i =0
	j = -1
inf.close()

