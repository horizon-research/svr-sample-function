import os
import subprocess
import time

# os.system("source ~/Documents/HLS/Vivado/2018.2/settings64.sh")
bits = [10, 16, 24, 32, 64]
integers = [5, 6, 7, 8, 9, 10, 15, 20, 25, 30]

result = open("result.txt", "w")

for i in bits:

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

result.close()
