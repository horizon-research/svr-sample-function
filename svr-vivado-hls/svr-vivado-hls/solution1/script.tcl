############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project svr-vivado-hls
set_top convert
add_files samplefunction.cpp
add_files samplefunction.h
add_files -tb FOV.cpp
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./svr-vivado-hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
