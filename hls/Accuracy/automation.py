import os
import subprocess
import time

# os.system("source ~/Documents/HLS/Vivado/2018.2/settings64.sh")
bits = [24,28,32,36,40,44,48,52,56,60,64]
count = 0
c = 0
for i in bits:
    integers = [round(bits[c]*0.5),round(bits[c]*0.4),round(bits[c]*0.3),round(bits[c]*0.2),round(bits[c]*0.1)]
    for j in integers:

        subprocess.Popen("python3 wf.py " + str(i) + " " + str(j), shell=True).wait()
        subprocess.Popen(["mv", "temp.h", "samplefunction.h"]).wait()
        subprocess.Popen("vivado_hls script.tcl", shell=True).wait()
        fn = str(count)+".txt"
        file = open(fn,"w")
        file.close()
        subprocess.Popen(["mv","testsvr/solution1/csim/build/test.txt",fn]).wait()
        count += 1
        subprocess.Popen("rm -rf testsvr",shell=True).wait()
    c += 1
subprocess.Popen("python3 calDiff.py",shell=True).wait()




