import sys
import os
import shutil
from shutil import copyfile


i = int(sys.argv[1])

f1 = open('fov.cpp', 'r')
f2 = open('temp2.cpp','w')
f3 = open("samplefunction.cpp", "r")
f4 = open("temp.cpp", "w")

codes = f1.readlines()
morecodes = f3.readlines()
content = ""

if i == 0:
	codes[17] = "\tsrc = cvLoadImage(\"480p.jpg\");\n"
	content = "\tconst int w = 720, h = 480;\n"
if i == 1:
	codes[17] = "\tsrc = cvLoadImage(\"720p.jpg\");\n"
	content = "\tconst int w = 1280, h = 720;\n"
if i == 2:
	codes[17] = "\tsrc = cvLoadImage(\"1080p.jpg\");\n"
	content = "\tconst int w = 1920, h = 1080;\n"
if i == 3:
	codes[17] = "\tsrc = cvLoadImage(\"2k.jpg\");\n"
	content = "\tconst int w = 2048, h = 1080;\n"
if i == 4:
	codes[17] = "\tsrc = cvLoadImage(\"4k.jpg\");\n"
	content = "\tconst int w = 3840, h = 2160;\n"

morecodes[5] = content
codes[9] = content

f2.writelines(codes)
f4.writelines(morecodes)
f1.close()
f2.close()
f3.close()
f4.close()

copyfile('temp2.cpp','fov.cpp')
copyfile('temp.cpp','samplefunction.cpp')

os.remove("temp.cpp")
os.remove("temp2.cpp")
