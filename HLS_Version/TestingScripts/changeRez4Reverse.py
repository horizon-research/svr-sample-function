import sys
import os
import shutil
from shutil import copyfile


i = int(sys.argv[1])

f1 = open('main.cc', 'r')
f2 = open('temp2.cpp','w')
f3 = open("reverse.h", "r")
f4 = open("temp.cpp", "w")

codes = f1.readlines()
morecodes = f3.readlines()
content = ""

if i == 0:
	codes[15] = "\tsrc = cvLoadImage(\"480p.jpg\");\n"
	morecodes[3] = "#define INPUT_WIDTH 720\n"
	morecodes[4] = "#define INPUT_HEIGHT 480\n"
	morecodes[5] = "#define fw 180\n"
	morecodes[6] = "#define fh 120\n"
if i == 1:
	codes[15] = "\tsrc = cvLoadImage(\"720p.jpg\");\n"
	morecodes[3] = "#define INPUT_WIDTH 1280\n"
	morecodes[4] = "#define INPUT_HEIGHT 720\n"
	morecodes[5] = "#define fw 320\n"
	morecodes[6] = "#define fh 180\n"
if i == 2:
	codes[15] = "\tsrc = cvLoadImage(\"1080p.jpg\");\n"
	morecodes[3] = "#define INPUT_WIDTH 1920\n"
	morecodes[4] = "#define INPUT_HEIGHT 1080\n"
	morecodes[5] = "#define fw 480\n"
	morecodes[6] = "#define fh 270\n"
if i == 3:
	codes[15] = "\tsrc = cvLoadImage(\"2k.jpg\");\n"
	morecodes[3] = "#define INPUT_WIDTH 2048\n"
	morecodes[4] = "#define INPUT_HEIGHT 1080\n"
	morecodes[5] = "#define fw 512\n"
	morecodes[6] = "#define fh 270\n"
if i == 4:
	codes[15] = "\tsrc = cvLoadImage(\"4k.jpg\");\n"
	morecodes[3] = "#define INPUT_WIDTH 3840\n"
	morecodes[4] = "#define INPUT_HEIGHT 2160\n"
	morecodes[5] = "#define fw 960\n"
	morecodes[6] = "#define fh 540\n"


f2.writelines(codes)
f4.writelines(morecodes)
f1.close()
f2.close()
f3.close()
f4.close()

copyfile('temp2.cpp','main.cc')
copyfile('temp.cpp','reverse.h')

os.remove("temp.cpp")
os.remove("temp2.cpp")
