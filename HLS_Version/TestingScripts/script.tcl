############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project testsvr
set_top crt
add_files reverse.h
add_files reverse.cc
add_files -tb main.cpp
open_solution "solution1"
set_part {xczu7ev-ffvc1156-2-e} -tool vivado
create_clock -period 10 -name default
#source "./testsvr/solution1/directives.tcl"
##csim_design
csynth_design
export_design -flow syn -rtl verilog -format ip_catalog
