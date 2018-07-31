import cv2
import math
import numpy as np

bits = [24,28,32,36,40,44,48,52,56,60,64]
integers = [2,6,7,8,9,10]
sample = cv2.imread("fov.jpg")
img = cv2.imread("cube.jpg")
fov = np.zeros((1024,1024,3), np.uint8)
cv2.waitKey(0)
i = 0
j = -1
rd = 0
gd = 0
bd = 0
res = 0
acurracy = open("Accuracy.txt","w")
count = 0
for num in bits:
    for count in integers:

        inf = open(str(count)+".txt","r")
        for line in inf:
	   
            m,n = line.split(",")
            a = i%1024
            if a == 0:
                j += 1
            fov[j,a] = img[int(n)-1, int(m)-1]
            #BGR
            rd += math.sqrt(((int)(fov[j,a,2]) -(int)(sample[j,a,2]))* ((int)(fov[j,a,2]) -(int)(sample[j,a,2])))
            gd += math.sqrt(((int)(fov[j,a,1]) -(int)(sample[j,a,1]))* ((int)(fov[j,a,1]) -(int)(sample[j,a,1])))
            bd += math.sqrt(((int)(fov[j,a,0]) -(int)(sample[j,a,0]))* ((int)(fov[j,a,0]) -(int)(sample[j,a,0])))
            i += 1
        inf.close()
        count += 1
        res = (rd+gd+bd)/1024/1024
        acurracy.write("------------<"+str(num)+","+str(count)+">------------\n")    
        acurracy.write("accuracy:"+ str(res)+"\n")
        acurracy.write("-----------------------------------------------------\n")
        i = 0
        j = -1
        rd = 0
        gd = 0
        bd = 0
        res = 0

acurracy.close()





    
