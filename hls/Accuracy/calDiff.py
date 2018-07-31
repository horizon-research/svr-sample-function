import math
import numpy as np

bits = [24,28,32,36,40,44,48,52,56,60,64]
i = 0
j = -1
res = 0
acurracy = open("Accuracy.txt","w")
sample = open("doubleResult.txt","r")
sampleData = sample.readlines()
c = 0
c1 = 0
for num in bits:
     integers = [round(bits[c1]*0.5),round(bits[c1]*0.4),round(bits[c1]*0.3),round(bits[c1]*0.2),round(bits[c1]*0.1)]
    for count in integers:

        inf = open(str(c)+".txt","r")
        infData = inf.readlines()
        for line in range(len(sampleData)):
	   
            m,n = infData[line].split(",")
            fm,fn = sampleData[line].split(",")
            a = i%1024
            if a == 0:
                j += 1
            rfm = float(fm) + 1
            rfn = float(fn) + 1
            
            #d = math.sqrt((rfm - (float)(m)) * (rfm - (float)(m))) + math.sqrt((rfn - (float)(n)) * (rfn - (float)(n)))
            d = (abs(round(rfm) - round((float)(m)))/1024.0 + abs(round(rfn) - round((float)(n)))/1024.0)/2
            res += d
            #print(d)
           # print("m:" + m + ", n:"+ n)
           # print("fm:" + fm + ", fn:"+ fn)
            i += 1
        inf.close()
        c += 1
        res /= 1024.0
        res /= 1024.0
        acurracy.write("------------<"+str(num)+","+str(count)+">------------\n")    
        acurracy.write("accuracy:"+ str(res)+"\n")
        acurracy.write("-----------------------------------------------------\n")
        i = 0
        j = -1
        res = 0
    c1 = 0

acurracy.close()
sample.close()





    
