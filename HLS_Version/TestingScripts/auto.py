import subprocess

for i in range(5):

    result = open('result.txt', 'w')

    subprocess.Popen("python changeRez4Reverse.py " + str(i), shell=True).wait()
    subprocess.Popen("vivado_hls script.tcl", shell=True).wait()

    hlsreport = open("testsvr/solution1/syn/report/crt_csynth.rpt", "r")
    hlsdata = hlsreport.readlines()
    result.write("==================================================================================\n")
    result.write("Timing (ns): \n")
    result.write(hlsdata[22])
    result.write("Latency (clock cycles):\n")
    result.write(hlsdata[31])
    result.write("Utilization (%): \n")
    result.write(hlsdata[76])

    subprocess.Popen("python mv.py", shell=True).wait()

    subprocess.Popen("vivado -mode batch -source testsvr/solution1/impl/verilog/data.tcl", shell=True).wait()

    power = open("power.txt")
    powerdata = power.readlines()

    for a in range(29, 47):
        result.write(powerdata[a])

    result.write("==================================================================================\n\n")
    result.close()
    hlsreport.close()
    power.close()
    subprocess.Popen("python packAllFile.py " + str(i), shell=True).wait()





