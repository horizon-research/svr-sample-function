############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project testsvr
set_top crt
add_files samplefunction.h
add_files samplefunction.cpp
add_files -tb fov.cpp
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 20 -name default
#source "./testsvr/solution1/directives.tcl"
##csim_design
csynth_design
export_design -flow syn -rtl verilog -format ip_catalog
