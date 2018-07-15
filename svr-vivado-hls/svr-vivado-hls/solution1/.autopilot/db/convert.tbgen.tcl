set C_TypeInfoList {{ 
"convert" : [[], { "return": [[], "void"]} , [{"ExternC" : 0}], [ {"width": [[], {"scalar": "int"}] }, {"height": [[], {"scalar": "int"}] }, {"hp": [[], {"scalar": "double"}] }, {"ht": [[], {"scalar": "double"}] }, {"fw": [[], {"scalar": "int"}] }, {"fh": [[], {"scalar": "int"}] }, {"fovX": [[], {"scalar": "int"}] }, {"fovY": [[], {"scalar": "int"}] }, {"option": [[], {"scalar": "int"}] }, {"fov": [[], {"array": [ {"array": [ {"scalar": "long double"}, [2000,2]]}, [2000]]}] }],["0","1","2","3"],""],
 "0": [ "w", [[], {"scalar": "int"}],""],
 "1": [ "tileSize", [[], {"scalar": "double"}],""],
 "2": [ "h", [[], {"scalar": "int"}],""],
 "3": [ "PI", [[], {"scalar": "long double"}],""]
}}
set moduleName convert
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {convert}
set C_modelType { void 0 }
set C_modelArgList {
	{ width int 32 regular  }
	{ height int 32 regular  }
	{ hp double 64 regular  }
	{ ht double 64 regular  }
	{ fw int 32 regular  }
	{ fh int 32 regular  }
	{ fovX int 32 regular  }
	{ fovY int 32 regular  }
	{ option int 32 regular  }
	{ fov int 80 regular {array 8000000 { 0 0 } 1 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "width", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "width","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "height", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "height","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "hp", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "hp","cData": "double","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "ht", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "ht","cData": "double","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "fw", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "fw","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "fh", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "fh","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "fovX", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "fovX","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "fovY", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "fovY","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "option", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "option","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "fov", "interface" : "memory", "bitwidth" : 80, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":79,"cElement": [{"cName": "fov","cData": "long double","bit_use": { "low": 0,"up": 79},"cArray": [{"low" : 0,"up" : 1999,"step" : 1},{"low" : 0,"up" : 1999,"step" : 1},{"low" : 0,"up" : 1,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 23
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ width sc_in sc_lv 32 signal 0 } 
	{ height sc_in sc_lv 32 signal 1 } 
	{ hp sc_in sc_lv 64 signal 2 } 
	{ ht sc_in sc_lv 64 signal 3 } 
	{ fw sc_in sc_lv 32 signal 4 } 
	{ fh sc_in sc_lv 32 signal 5 } 
	{ fovX sc_in sc_lv 32 signal 6 } 
	{ fovY sc_in sc_lv 32 signal 7 } 
	{ option sc_in sc_lv 32 signal 8 } 
	{ fov_address0 sc_out sc_lv 23 signal 9 } 
	{ fov_ce0 sc_out sc_logic 1 signal 9 } 
	{ fov_we0 sc_out sc_logic 1 signal 9 } 
	{ fov_d0 sc_out sc_lv 80 signal 9 } 
	{ fov_address1 sc_out sc_lv 23 signal 9 } 
	{ fov_ce1 sc_out sc_logic 1 signal 9 } 
	{ fov_we1 sc_out sc_logic 1 signal 9 } 
	{ fov_d1 sc_out sc_lv 80 signal 9 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "width", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "width", "role": "default" }} , 
 	{ "name": "height", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "height", "role": "default" }} , 
 	{ "name": "hp", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "hp", "role": "default" }} , 
 	{ "name": "ht", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "ht", "role": "default" }} , 
 	{ "name": "fw", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "fw", "role": "default" }} , 
 	{ "name": "fh", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "fh", "role": "default" }} , 
 	{ "name": "fovX", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "fovX", "role": "default" }} , 
 	{ "name": "fovY", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "fovY", "role": "default" }} , 
 	{ "name": "option", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "option", "role": "default" }} , 
 	{ "name": "fov_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":23, "type": "signal", "bundle":{"name": "fov", "role": "address0" }} , 
 	{ "name": "fov_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fov", "role": "ce0" }} , 
 	{ "name": "fov_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fov", "role": "we0" }} , 
 	{ "name": "fov_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":80, "type": "signal", "bundle":{"name": "fov", "role": "d0" }} , 
 	{ "name": "fov_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":23, "type": "signal", "bundle":{"name": "fov", "role": "address1" }} , 
 	{ "name": "fov_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fov", "role": "ce1" }} , 
 	{ "name": "fov_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fov", "role": "we1" }} , 
 	{ "name": "fov_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":80, "type": "signal", "bundle":{"name": "fov", "role": "d1" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "7", "28", "49", "70", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123"],
		"CDFG" : "convert",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "82", "EstimateLatencyMax" : "5654990",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state244", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_atan2_cordic_double_s_fu_315"},
			{"State" : "ap_ST_fsm_state39", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_323"},
			{"State" : "ap_ST_fsm_state129", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_323"},
			{"State" : "ap_ST_fsm_state141", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_323"},
			{"State" : "ap_ST_fsm_state39", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_342"},
			{"State" : "ap_ST_fsm_state129", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_342"},
			{"State" : "ap_ST_fsm_state39", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_361"},
			{"State" : "ap_ST_fsm_state129", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_361"},
			{"State" : "ap_ST_fsm_state39", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_sin_or_cos_double_s_fu_380"}],
		"Port" : [
			{"Name" : "width", "Type" : "None", "Direction" : "I"},
			{"Name" : "height", "Type" : "None", "Direction" : "I"},
			{"Name" : "hp", "Type" : "None", "Direction" : "I"},
			{"Name" : "ht", "Type" : "None", "Direction" : "I"},
			{"Name" : "fw", "Type" : "None", "Direction" : "I"},
			{"Name" : "fh", "Type" : "None", "Direction" : "I"},
			{"Name" : "fovX", "Type" : "None", "Direction" : "I"},
			{"Name" : "fovY", "Type" : "None", "Direction" : "I"},
			{"Name" : "option", "Type" : "None", "Direction" : "I"},
			{"Name" : "fov", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "w", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "h", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "ref_4oPi_table_256_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "28", "SubInstance" : "grp_sin_or_cos_double_s_fu_342", "Port" : "ref_4oPi_table_256_V"},
					{"ID" : "70", "SubInstance" : "grp_sin_or_cos_double_s_fu_380", "Port" : "ref_4oPi_table_256_V"},
					{"ID" : "7", "SubInstance" : "grp_sin_or_cos_double_s_fu_323", "Port" : "ref_4oPi_table_256_V"},
					{"ID" : "49", "SubInstance" : "grp_sin_or_cos_double_s_fu_361", "Port" : "ref_4oPi_table_256_V"}]},
			{"Name" : "fourth_order_double_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "28", "SubInstance" : "grp_sin_or_cos_double_s_fu_342", "Port" : "fourth_order_double_4"},
					{"ID" : "70", "SubInstance" : "grp_sin_or_cos_double_s_fu_380", "Port" : "fourth_order_double_4"},
					{"ID" : "7", "SubInstance" : "grp_sin_or_cos_double_s_fu_323", "Port" : "fourth_order_double_4"},
					{"ID" : "49", "SubInstance" : "grp_sin_or_cos_double_s_fu_361", "Port" : "fourth_order_double_4"}]},
			{"Name" : "fourth_order_double_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "28", "SubInstance" : "grp_sin_or_cos_double_s_fu_342", "Port" : "fourth_order_double_5"},
					{"ID" : "70", "SubInstance" : "grp_sin_or_cos_double_s_fu_380", "Port" : "fourth_order_double_5"},
					{"ID" : "7", "SubInstance" : "grp_sin_or_cos_double_s_fu_323", "Port" : "fourth_order_double_5"},
					{"ID" : "49", "SubInstance" : "grp_sin_or_cos_double_s_fu_361", "Port" : "fourth_order_double_5"}]},
			{"Name" : "fourth_order_double_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "28", "SubInstance" : "grp_sin_or_cos_double_s_fu_342", "Port" : "fourth_order_double_6"},
					{"ID" : "70", "SubInstance" : "grp_sin_or_cos_double_s_fu_380", "Port" : "fourth_order_double_6"},
					{"ID" : "7", "SubInstance" : "grp_sin_or_cos_double_s_fu_323", "Port" : "fourth_order_double_6"},
					{"ID" : "49", "SubInstance" : "grp_sin_or_cos_double_s_fu_361", "Port" : "fourth_order_double_6"}]},
			{"Name" : "fourth_order_double_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "28", "SubInstance" : "grp_sin_or_cos_double_s_fu_342", "Port" : "fourth_order_double_7"},
					{"ID" : "70", "SubInstance" : "grp_sin_or_cos_double_s_fu_380", "Port" : "fourth_order_double_7"},
					{"ID" : "7", "SubInstance" : "grp_sin_or_cos_double_s_fu_323", "Port" : "fourth_order_double_7"},
					{"ID" : "49", "SubInstance" : "grp_sin_or_cos_double_s_fu_361", "Port" : "fourth_order_double_7"}]},
			{"Name" : "fourth_order_double_s", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "28", "SubInstance" : "grp_sin_or_cos_double_s_fu_342", "Port" : "fourth_order_double_s"},
					{"ID" : "70", "SubInstance" : "grp_sin_or_cos_double_s_fu_380", "Port" : "fourth_order_double_s"},
					{"ID" : "7", "SubInstance" : "grp_sin_or_cos_double_s_fu_323", "Port" : "fourth_order_double_s"},
					{"ID" : "49", "SubInstance" : "grp_sin_or_cos_double_s_fu_361", "Port" : "fourth_order_double_s"}]},
			{"Name" : "cordic_ctab_table_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_atan2_cordic_double_s_fu_315", "Port" : "cordic_ctab_table_12"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_atan2_cordic_double_s_fu_315", "Parent" : "0", "Child" : ["2", "5", "6"],
		"CDFG" : "atan2_cordic_double_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "1", "EstimateLatencyMax" : "284",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state2", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_atan2_generic_fu_171"},
			{"State" : "ap_ST_fsm_state3", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_atan2_generic_fu_171"}],
		"Port" : [
			{"Name" : "y_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "x_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "cordic_ctab_table_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_atan2_generic_fu_171", "Port" : "cordic_ctab_table_12"}]}]},
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_atan2_cordic_double_s_fu_315.grp_atan2_generic_fu_171", "Parent" : "1", "Child" : ["3", "4"],
		"CDFG" : "atan2_generic",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "1", "EstimateLatencyMax" : "271",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "y_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "x_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "cordic_ctab_table_12", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "3", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_atan2_cordic_double_s_fu_315.grp_atan2_generic_fu_171.cordic_ctab_table_12_U", "Parent" : "2"},
	{"ID" : "4", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_atan2_cordic_double_s_fu_315.grp_atan2_generic_fu_171.convert_ddiv_64nsrcU_U34", "Parent" : "2"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_atan2_cordic_double_s_fu_315.convert_dsub_64nssc4_U39", "Parent" : "1"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_atan2_cordic_double_s_fu_315.convert_dcmp_64nstde_U40", "Parent" : "1"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323", "Parent" : "0", "Child" : ["8", "9", "10", "11", "12", "13", "14", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27"],
		"CDFG" : "sin_or_cos_double_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "43", "EstimateLatencyMax" : "51",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state24", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_scaled_fixed2ieee_fu_268"}],
		"Port" : [
			{"Name" : "t_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "do_cos", "Type" : "None", "Direction" : "I"},
			{"Name" : "ref_4oPi_table_256_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_s", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.ref_4oPi_table_256_V_U", "Parent" : "7"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.fourth_order_double_4_U", "Parent" : "7"},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.fourth_order_double_5_U", "Parent" : "7"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.fourth_order_double_6_U", "Parent" : "7"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.fourth_order_double_7_U", "Parent" : "7"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.fourth_order_double_s_U", "Parent" : "7"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.grp_scaled_fixed2ieee_fu_268", "Parent" : "7", "Child" : ["15", "16"],
		"CDFG" : "scaled_fixed2ieee",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "19", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "in_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "prescale", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "15", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U1", "Parent" : "14"},
	{"ID" : "16", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U2", "Parent" : "14"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_170nsibs_U6", "Parent" : "7"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mux_83_1_jbC_U7", "Parent" : "7"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_49ns_kbM_U8", "Parent" : "7"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_49ns_kbM_U9", "Parent" : "7"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_49ns_kbM_U10", "Parent" : "7"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_56ns_lbW_U11", "Parent" : "7"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_49ns_mb6_U12", "Parent" : "7"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_42ns_ncg_U13", "Parent" : "7"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mul_64s_6ocq_U14", "Parent" : "7"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mux_164_1pcA_U15", "Parent" : "7"},
	{"ID" : "27", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_323.convert_mux_164_1pcA_U16", "Parent" : "7"},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342", "Parent" : "0", "Child" : ["29", "30", "31", "32", "33", "34", "35", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48"],
		"CDFG" : "sin_or_cos_double_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "43", "EstimateLatencyMax" : "51",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state24", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_scaled_fixed2ieee_fu_268"}],
		"Port" : [
			{"Name" : "t_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "do_cos", "Type" : "None", "Direction" : "I"},
			{"Name" : "ref_4oPi_table_256_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_s", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.ref_4oPi_table_256_V_U", "Parent" : "28"},
	{"ID" : "30", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.fourth_order_double_4_U", "Parent" : "28"},
	{"ID" : "31", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.fourth_order_double_5_U", "Parent" : "28"},
	{"ID" : "32", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.fourth_order_double_6_U", "Parent" : "28"},
	{"ID" : "33", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.fourth_order_double_7_U", "Parent" : "28"},
	{"ID" : "34", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.fourth_order_double_s_U", "Parent" : "28"},
	{"ID" : "35", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.grp_scaled_fixed2ieee_fu_268", "Parent" : "28", "Child" : ["36", "37"],
		"CDFG" : "scaled_fixed2ieee",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "19", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "in_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "prescale", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "36", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U1", "Parent" : "35"},
	{"ID" : "37", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U2", "Parent" : "35"},
	{"ID" : "38", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_170nsibs_U6", "Parent" : "28"},
	{"ID" : "39", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mux_83_1_jbC_U7", "Parent" : "28"},
	{"ID" : "40", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_49ns_kbM_U8", "Parent" : "28"},
	{"ID" : "41", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_49ns_kbM_U9", "Parent" : "28"},
	{"ID" : "42", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_49ns_kbM_U10", "Parent" : "28"},
	{"ID" : "43", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_56ns_lbW_U11", "Parent" : "28"},
	{"ID" : "44", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_49ns_mb6_U12", "Parent" : "28"},
	{"ID" : "45", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_42ns_ncg_U13", "Parent" : "28"},
	{"ID" : "46", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mul_64s_6ocq_U14", "Parent" : "28"},
	{"ID" : "47", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mux_164_1pcA_U15", "Parent" : "28"},
	{"ID" : "48", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_342.convert_mux_164_1pcA_U16", "Parent" : "28"},
	{"ID" : "49", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361", "Parent" : "0", "Child" : ["50", "51", "52", "53", "54", "55", "56", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69"],
		"CDFG" : "sin_or_cos_double_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "43", "EstimateLatencyMax" : "51",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state24", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_scaled_fixed2ieee_fu_268"}],
		"Port" : [
			{"Name" : "t_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "do_cos", "Type" : "None", "Direction" : "I"},
			{"Name" : "ref_4oPi_table_256_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_s", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "50", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.ref_4oPi_table_256_V_U", "Parent" : "49"},
	{"ID" : "51", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.fourth_order_double_4_U", "Parent" : "49"},
	{"ID" : "52", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.fourth_order_double_5_U", "Parent" : "49"},
	{"ID" : "53", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.fourth_order_double_6_U", "Parent" : "49"},
	{"ID" : "54", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.fourth_order_double_7_U", "Parent" : "49"},
	{"ID" : "55", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.fourth_order_double_s_U", "Parent" : "49"},
	{"ID" : "56", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.grp_scaled_fixed2ieee_fu_268", "Parent" : "49", "Child" : ["57", "58"],
		"CDFG" : "scaled_fixed2ieee",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "19", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "in_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "prescale", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "57", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U1", "Parent" : "56"},
	{"ID" : "58", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U2", "Parent" : "56"},
	{"ID" : "59", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_170nsibs_U6", "Parent" : "49"},
	{"ID" : "60", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mux_83_1_jbC_U7", "Parent" : "49"},
	{"ID" : "61", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_49ns_kbM_U8", "Parent" : "49"},
	{"ID" : "62", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_49ns_kbM_U9", "Parent" : "49"},
	{"ID" : "63", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_49ns_kbM_U10", "Parent" : "49"},
	{"ID" : "64", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_56ns_lbW_U11", "Parent" : "49"},
	{"ID" : "65", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_49ns_mb6_U12", "Parent" : "49"},
	{"ID" : "66", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_42ns_ncg_U13", "Parent" : "49"},
	{"ID" : "67", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mul_64s_6ocq_U14", "Parent" : "49"},
	{"ID" : "68", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mux_164_1pcA_U15", "Parent" : "49"},
	{"ID" : "69", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_361.convert_mux_164_1pcA_U16", "Parent" : "49"},
	{"ID" : "70", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380", "Parent" : "0", "Child" : ["71", "72", "73", "74", "75", "76", "77", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90"],
		"CDFG" : "sin_or_cos_double_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "43", "EstimateLatencyMax" : "51",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state24", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_scaled_fixed2ieee_fu_268"}],
		"Port" : [
			{"Name" : "t_in", "Type" : "None", "Direction" : "I"},
			{"Name" : "do_cos", "Type" : "None", "Direction" : "I"},
			{"Name" : "ref_4oPi_table_256_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_s", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "71", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.ref_4oPi_table_256_V_U", "Parent" : "70"},
	{"ID" : "72", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.fourth_order_double_4_U", "Parent" : "70"},
	{"ID" : "73", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.fourth_order_double_5_U", "Parent" : "70"},
	{"ID" : "74", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.fourth_order_double_6_U", "Parent" : "70"},
	{"ID" : "75", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.fourth_order_double_7_U", "Parent" : "70"},
	{"ID" : "76", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.fourth_order_double_s_U", "Parent" : "70"},
	{"ID" : "77", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.grp_scaled_fixed2ieee_fu_268", "Parent" : "70", "Child" : ["78", "79"],
		"CDFG" : "scaled_fixed2ieee",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "19", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "in_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "prescale", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "78", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U1", "Parent" : "77"},
	{"ID" : "79", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.grp_scaled_fixed2ieee_fu_268.convert_mux_42_32bkb_U2", "Parent" : "77"},
	{"ID" : "80", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_170nsibs_U6", "Parent" : "70"},
	{"ID" : "81", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mux_83_1_jbC_U7", "Parent" : "70"},
	{"ID" : "82", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_49ns_kbM_U8", "Parent" : "70"},
	{"ID" : "83", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_49ns_kbM_U9", "Parent" : "70"},
	{"ID" : "84", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_49ns_kbM_U10", "Parent" : "70"},
	{"ID" : "85", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_56ns_lbW_U11", "Parent" : "70"},
	{"ID" : "86", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_49ns_mb6_U12", "Parent" : "70"},
	{"ID" : "87", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_42ns_ncg_U13", "Parent" : "70"},
	{"ID" : "88", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mul_64s_6ocq_U14", "Parent" : "70"},
	{"ID" : "89", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mux_164_1pcA_U15", "Parent" : "70"},
	{"ID" : "90", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_sin_or_cos_double_s_fu_380.convert_mux_164_1pcA_U16", "Parent" : "70"},
	{"ID" : "91", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fptrunc_8udo_U45", "Parent" : "0"},
	{"ID" : "92", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fptrunc_8udo_U46", "Parent" : "0"},
	{"ID" : "93", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U47", "Parent" : "0"},
	{"ID" : "94", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U48", "Parent" : "0"},
	{"ID" : "95", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U49", "Parent" : "0"},
	{"ID" : "96", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U50", "Parent" : "0"},
	{"ID" : "97", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U51", "Parent" : "0"},
	{"ID" : "98", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U52", "Parent" : "0"},
	{"ID" : "99", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U53", "Parent" : "0"},
	{"ID" : "100", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U54", "Parent" : "0"},
	{"ID" : "101", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U55", "Parent" : "0"},
	{"ID" : "102", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U56", "Parent" : "0"},
	{"ID" : "103", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_fpext_64nvdy_U57", "Parent" : "0"},
	{"ID" : "104", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dadddsub_wdI_U58", "Parent" : "0"},
	{"ID" : "105", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dadddsub_wdI_U59", "Parent" : "0"},
	{"ID" : "106", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dmul_80nsxdS_U60", "Parent" : "0"},
	{"ID" : "107", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dmul_80nsxdS_U61", "Parent" : "0"},
	{"ID" : "108", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dmul_80nsxdS_U62", "Parent" : "0"},
	{"ID" : "109", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dmul_80nsxdS_U63", "Parent" : "0"},
	{"ID" : "110", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_ddiv_80nsyd2_U64", "Parent" : "0"},
	{"ID" : "111", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_ddiv_80nsyd2_U65", "Parent" : "0"},
	{"ID" : "112", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_ddiv_64nsrcU_U66", "Parent" : "0"},
	{"ID" : "113", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dcmp_80nszec_U67", "Parent" : "0"},
	{"ID" : "114", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dcmp_80nszec_U68", "Parent" : "0"},
	{"ID" : "115", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dcmp_64nstde_U69", "Parent" : "0"},
	{"ID" : "116", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dcmp_64nstde_U70", "Parent" : "0"},
	{"ID" : "117", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dcmp_64nstde_U71", "Parent" : "0"},
	{"ID" : "118", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_dcmp_64nstde_U72", "Parent" : "0"},
	{"ID" : "119", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_sitodp_32Aem_U73", "Parent" : "0"},
	{"ID" : "120", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_sitodp_32Bew_U74", "Parent" : "0"},
	{"ID" : "121", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_sitodp_32Bew_U75", "Parent" : "0"},
	{"ID" : "122", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_sitodp_32Bew_U76", "Parent" : "0"},
	{"ID" : "123", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.convert_sitodp_32Bew_U77", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	convert {
		width {Type I LastRead 1 FirstWrite -1}
		height {Type I LastRead 38 FirstWrite -1}
		hp {Type I LastRead 0 FirstWrite -1}
		ht {Type I LastRead 0 FirstWrite -1}
		fw {Type I LastRead 1 FirstWrite -1}
		fh {Type I LastRead 1 FirstWrite -1}
		fovX {Type I LastRead 1 FirstWrite -1}
		fovY {Type I LastRead 1 FirstWrite -1}
		option {Type I LastRead 38 FirstWrite -1}
		fov {Type O LastRead -1 FirstWrite 258}
		w {Type IO LastRead -1 FirstWrite -1}
		h {Type IO LastRead -1 FirstWrite -1}
		ref_4oPi_table_256_V {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_4 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_5 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_6 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_7 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_s {Type I LastRead -1 FirstWrite -1}
		cordic_ctab_table_12 {Type I LastRead -1 FirstWrite -1}}
	atan2_cordic_double_s {
		y_in {Type I LastRead 0 FirstWrite -1}
		x_in {Type I LastRead 0 FirstWrite -1}
		cordic_ctab_table_12 {Type I LastRead -1 FirstWrite -1}}
	atan2_generic {
		y_in {Type I LastRead 0 FirstWrite -1}
		x_in {Type I LastRead 0 FirstWrite -1}
		cordic_ctab_table_12 {Type I LastRead -1 FirstWrite -1}}
	sin_or_cos_double_s {
		t_in {Type I LastRead 0 FirstWrite -1}
		do_cos {Type I LastRead 11 FirstWrite -1}
		ref_4oPi_table_256_V {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_4 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_5 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_6 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_7 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_s {Type I LastRead -1 FirstWrite -1}}
	scaled_fixed2ieee {
		in_V {Type I LastRead 0 FirstWrite -1}
		prescale {Type I LastRead 0 FirstWrite -1}}
	sin_or_cos_double_s {
		t_in {Type I LastRead 0 FirstWrite -1}
		do_cos {Type I LastRead 11 FirstWrite -1}
		ref_4oPi_table_256_V {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_4 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_5 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_6 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_7 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_s {Type I LastRead -1 FirstWrite -1}}
	scaled_fixed2ieee {
		in_V {Type I LastRead 0 FirstWrite -1}
		prescale {Type I LastRead 0 FirstWrite -1}}
	sin_or_cos_double_s {
		t_in {Type I LastRead 0 FirstWrite -1}
		do_cos {Type I LastRead 11 FirstWrite -1}
		ref_4oPi_table_256_V {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_4 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_5 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_6 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_7 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_s {Type I LastRead -1 FirstWrite -1}}
	scaled_fixed2ieee {
		in_V {Type I LastRead 0 FirstWrite -1}
		prescale {Type I LastRead 0 FirstWrite -1}}
	sin_or_cos_double_s {
		t_in {Type I LastRead 0 FirstWrite -1}
		do_cos {Type I LastRead 11 FirstWrite -1}
		ref_4oPi_table_256_V {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_4 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_5 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_6 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_7 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_s {Type I LastRead -1 FirstWrite -1}}
	scaled_fixed2ieee {
		in_V {Type I LastRead 0 FirstWrite -1}
		prescale {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "82", "Max" : "5654990"}
	, {"Name" : "Interval", "Min" : "83", "Max" : "5654991"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	width { ap_none {  { width in_data 0 32 } } }
	height { ap_none {  { height in_data 0 32 } } }
	hp { ap_none {  { hp in_data 0 64 } } }
	ht { ap_none {  { ht in_data 0 64 } } }
	fw { ap_none {  { fw in_data 0 32 } } }
	fh { ap_none {  { fh in_data 0 32 } } }
	fovX { ap_none {  { fovX in_data 0 32 } } }
	fovY { ap_none {  { fovY in_data 0 32 } } }
	option { ap_none {  { option in_data 0 32 } } }
	fov { ap_memory {  { fov_address0 mem_address 1 23 }  { fov_ce0 mem_ce 1 1 }  { fov_we0 mem_we 1 1 }  { fov_d0 mem_din 1 80 }  { fov_address1 mem_address 1 23 }  { fov_ce1 mem_ce 1 1 }  { fov_we1 mem_we 1 1 }  { fov_d1 mem_din 1 80 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
