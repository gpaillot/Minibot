transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test {C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test/UART_Dynamixel.sv}
vlog -sv -work work +incdir+C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test {C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test/Dyna_test.sv}

vlog -sv -work work +incdir+C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test {C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test/MyTestBench.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  MyTestBench

do C:/Users/GuiP/Documents/GitHub/Minibot/Dynamixel/Dyna_test/simulation/modelsim/wave.do
