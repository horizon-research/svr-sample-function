import os
import subprocess
import time

# os.system("source ~/Documents/HLS/Vivado/2018.2/settings64.sh")
bits = [24,28,32,36,40,44,48,52,56,60,64]

c = 0
result = open("result.txt", "w")

for i in bits:
    integers = [round(bits[c]*0.5),round(bits[c]*0.4),round(bits[c]*0.3),round(bits[c]*0.2),round(bits[c]*0.1)]
    for j in integers:

        if j < i:

            subprocess.Popen("python3 wf.py " + str(i) + " " + str(j), shell=True).wait()
            subprocess.Popen(["mv", "temp.h", "samplefunction.h"]).wait()
            subprocess.Popen("vivado_hls script.tcl", shell=True).wait()
            hlsreport = open("testsvr/solution1/syn/report/crt_csynth.rpt", "r")
            hlsdata = hlsreport.readlines()
            result.write("==================================================================================\n")
            result.write("*******<" + str(i) + "," + str(j) + ">"+"*******")
            result.write("Timing (ns): \n")
            result.write(hlsdata[22])
            result.write("Latency (clock cycles):\n")
            result.write(hlsdata[31])
            result.write("Utilization (%): \n")
            result.write(hlsdata[72])
            subprocess.Popen("mv testsvr/solution1/impl/ip/hdl/verilog/*.v verilogs", shell=True).wait()
            subprocess.Popen(["vivado", "-mode", "batch", "-source", "verilogs/data.tcl"]).wait()

            power = open("power.txt")
            powerdata = power.readlines()

            for a in range(50, 67):
                result.write(powerdata[a])

            result.write("==================================================================================\n\n")

            subprocess.Popen("rm *.backup*", shell=True).wait()
            subprocess.Popen("rm verilogs/*.v", shell=True).wait()
            hlsreport.close()
            power.close()
    c += 1
result.close()
