import shutil
import os
import sys

resolutions = {0: "480p", 1: "720p", 2: "1080p", 3: "2k", 4: "4k"}

shutil.move("result.txt", "testsvr/result.txt")

if os.path.exists("power.txt"):
    shutil.move("power.txt", "testsvr/power.txt")
if os.path.exists("testsvr/vivado_hls.log"):
    shutil.move("vivado_hls.log", "testsvr/vivadohls.log")
else:
    shutil.move("vivado_hls.log", "testsvr")

if os.path.exists("testsvr/vivado.log"):
    shutil.move("vivado.log", "testsvr/vivado1.log")
else:
    shutil.move("vivado.log", "testsvr/vivado.log")

res = int(sys.argv[1])

shutil.move("testsvr", resolutions[res])
