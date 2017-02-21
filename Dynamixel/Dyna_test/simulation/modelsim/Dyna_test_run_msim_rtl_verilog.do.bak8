transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/GuiP/Documents/1_EPL/MA1/Projet_mecatro/Dynamixel/Dyna_test {C:/Users/GuiP/Documents/1_EPL/MA1/Projet_mecatro/Dynamixel/Dyna_test/UART_Dynamixel.sv}
vlog -sv -work work +incdir+C:/Users/GuiP/Documents/1_EPL/MA1/Projet_mecatro/Dynamixel/Dyna_test {C:/Users/GuiP/Documents/1_EPL/MA1/Projet_mecatro/Dynamixel/Dyna_test/Dyna_test.sv}

vlog -sv -work work +incdir+C:/Users/GuiP/Documents/1_EPL/MA1/Projet_mecatro/Dynamixel/Dyna_test {C:/Users/GuiP/Documents/1_EPL/MA1/Projet_mecatro/Dynamixel/Dyna_test/MyTestBench.sv}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  MyTestBench

add wave *
view structure
view signals
run -all
