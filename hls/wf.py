import sys

i = sys.argv[1]
j = sys.argv[2]

f1 = open("samplefunction.h", "r")
f2 = open("temp.h", "w")
fp = f1.readlines()
content = "typedef ap_fixed<" + str(i) + "," + str(j) + "> fp;\n"
fp[7] = content
f2.writelines(fp)
f1.close()
f2.close()

