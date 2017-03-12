onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -height 25 -radix binary /MyTestBench/dut/Thierry/reset
add wave -noupdate -height 25 /MyTestBench/KEY0
add wave -noupdate -height 25 /MyTestBench/dut/state
add wave -noupdate -height 25 /MyTestBench/sw
add wave -noupdate -height 25 -radix binary /MyTestBench/dut/Thierry/write_en
add wave -noupdate -height 25 -radix binary /MyTestBench/dut/Thierry/read_en
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/rw_ad
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/write_data
add wave -noupdate -height 25 -radix binary /MyTestBench/dut/Thierry/TXD
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/UART_DIR
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/debug
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/baud_clk
add wave -noupdate -height 25 /MyTestBench/dut/TXD_Done
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/RXD_enable
add wave -noupdate -color Navy -height 25 /MyTestBench/dut/Thierry/RXD_done
add wave -noupdate -color Navy -height 25 /MyTestBench/dut/Thierry/start_RX
add wave -noupdate -color Navy -height 25 /MyTestBench/dut/Thierry/TXD_enable_prev
add wave -noupdate -color Navy -height 25 /MyTestBench/dut/Thierry/TXD_enable
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/TXD_data_1
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/TXD_data_2
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/RXD_data_1
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/RXD_data_2
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/communication_fail
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/start_communication
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/read_data
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/txd/frame
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/txd/data1
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/txd/data2
add wave -noupdate -height 25 -radix hexadecimal /MyTestBench/dut/Thierry/txd/ubyte/buffer
add wave -noupdate -height 25 /MyTestBench/dut/Thierry/txd/ubyte/out
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 5} {3568585426 ps} 0} {{Cursor 6} {9997925749 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 89
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {10500 us}
